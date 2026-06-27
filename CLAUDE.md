# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

- MSBuild solution: `LaggySdk.sln` produces a static library (`LaggySdk.lib`).
- Toolset: `v143` (Visual Studio 2022), C++ standard: **C++20** (`/std:c++20`), `ConformanceMode=true`, **`TreatWarningAsError=true`** at WarningLevel 3 — warnings WILL break the build.
- Configurations: `Debug|x64`, `Release|x64`, `Debug|Win32`, `Release|Win32`.
- Uses a precompiled header: `stdafx.h` / `stdafx.cpp`. Every `.cpp` in the project must `#include "stdafx.h"` as its first include. `stdafx.cpp` is the only file with `PrecompiledHeader=Create`.

Command-line build (from repo root):

```
msbuild LaggySdk.sln /p:Configuration=Debug /p:Platform=x64
```

There is no test project and no lint configuration in the repository.

## Architecture

This is a small, reusable Windows/C++ SDK consumed by other projects (it builds a `.lib`, not an executable). Everything lives in the `Sdk` namespace. Source is flat under `LaggySdk/` — there is no subfolder structure.

A few pieces tie the whole library together; understanding them up front avoids a lot of confusion when reading individual headers.

### Forward declarations live in `SdkFwd.h`

`SdkFwd.h` is the canonical forward-declaration header for the SDK's core types (`EntityId`, `UniqueId`, `EventHandler`, `IEvent`, `ISerializable`, `IState`, `ITransition`, `Message`, `Registry`, `Window`, plus `Json::Value`). Prefer including `SdkFwd.h` in other headers instead of the full type headers — this is what keeps compile times manageable behind the PCH.

### Contracts: error model

`Contracts.h` defines the exception hierarchy (`DxException` → `AssertFailedException`, `PreconditionFailedException`, `PostconditionFailedException`, `DereferenceFailedException`, `DeadEndException`) and the macros that throw them:

- `CONTRACT_ASSERT(cond, msg)` — invariant
- `CONTRACT_EXPECT(cond, msg)` — precondition
- `CONTRACT_ENSURE(cond, msg)` — postcondition
- `CONTRACT_THROW(msg)` — unreachable / dead end
- `SAFE_DEREF(ptr, msg)` — dereference-or-throw

Use these instead of `assert`, raw `throw`, or null checks. They embed `__FILE__ : __LINE__` automatically.

### Registry: ECS-style component store, also an EventHandler

`Registry` (in `Registry.h`) is a type-indexed component store: `create()` mints an `EntityId`, then `add<C>`, `find<C>`, `get<C>`, `all<C>`, `remove` operate on per-type `std::unordered_map<EntityId, C>` pools. Pools are created lazily on first access via `std::type_index(typeid(C))`. Most accessors are template-inlined in the header — `Registry.cpp` is intentionally near-empty.

Note that `Registry` **inherits from `EventHandler`**, so a registry can be connected into the event graph and forward/handle events directly.

### EventHandler: bidirectional pub/sub graph

`EventHandler` (`EventHandler.h`/`.cpp`) implements a connection-based event system, not a topic system:

- `connectTo(other)` makes `other` a server and `*this` a client of `other`.
- `notify(event)` walks `d_clients` and calls `processEvent(event)` on each.
- The destructor calls both `disconnectFromAll()` and `disconnectAllFromSelf()`, so destroying a handler safely unwires it from both directions of the graph.

Subclasses override `processEvent(const IEvent&)` and typically `dynamic_cast` to the concrete `IEvent` subtype. `IEvent` itself is just a virtual-destructor base.

### Serialization: a JSON reflection layer over JsonCpp

`ISerializable` + `SerializableBase` + `SerializableField<T>` + `SerializableObject` + `SerializableShared<T>` + `SerializableOptional<T>` + `SerializableVector<T>` form a small reflection layer on top of bundled JsonCpp (`json.h`, `json-forwards.h`, `jsoncpp.cpp`).

The pattern for making a type serializable:

1. Inherit `ISerializable` and implement `pushFields()`.
2. Inside `pushFields()`, call `pushField("name", member)` for primitives, `pushObject(...)` for nested `ISerializable`s, `pushSharedPtr`, `pushOptional`, or `pushVector` as needed.
3. Primitive serialization for each `T` is dispatched via free functions `writeJson`/`readJson` in `Serializers.h`. Adding a new primitive type means overloading these.

`getUnderlyingField` uses an `is_base_of<ISerializable, T>` tag-dispatch trick (in the anonymous namespace inside `ISerializable.h`) to pick between `SerializableField` and `SerializableObject` automatically inside containers — so `pushVector<MySerializable>(...)` and `pushVector<int>(...)` both work without extra code at the call site.

`JsonHelper` / `JsonSerializer` are higher-level convenience wrappers; `ISerializable.h` is the core mechanism.

### Mixin interfaces (`I*.h`)

Many headers named `I*.h` are **not abstract** — they are concrete mixin classes that add a single piece of state plus get/set: `IPosition3`, `IRotation3`, `IScale3`, `ISpeed3`, `IVisibility`, `ITaggable`, `IModelName`, `ITextureName`, `IUniqueId`. Compose them via multiple inheritance on game/entity types. `IState`, `ITransition`, `IEvent`, `ICastable`, `ILockable`, `ISerializable` are the actual abstract interfaces.

### Other notable pieces

- `Graph.h` — header-only `Graph<NodeData, EdgeData>`: a generic graph with arbitrary payloads on every node and edge, addressed by `NodeId`/`EdgeId` handles (vector indices). Supports **removal**: `removeNode`/`removeEdge` mark an element dead and unwire it, and `getNodeIds`/`getEdgeIds`/`getEdgesAt`/`hasNode`/`hasEdge` then report only live elements — handles stay stable across removals (removed slots are tombstoned, not erased). `cleanup()` physically compacts the vectors and remaps every surviving handle (so it invalidates all outstanding ids). Edges are stored directed but `getEdgesAt(node)` reports them undirected (so its size is the node's live degree).
- `Spline.h` — header-only `Spline<T>` (aliases `SplineF`/`SplineD`/`SplineI`): a generic **Catmull-Rom** spline through 2D control points (stored as a `Polyline2<T>`). Passes through every point; endpoints clamp the phantom neighbours so the curve reaches its ends. Exposes `getSegmentsCount()`, `pointAt(seg, t)`/`tangentAt(seg, t)`, `sampleByStep(stepLen)` and `getControlPoints()` — both return a `Polyline2<T>` (the constructor still accepts a bare point vector, since `Polyline2` is implicitly constructible from one). Domain-neutral — no curve consumer's concepts leak in (e.g. lane offsetting belongs in the caller). Templated, builds on `Polyline.h` + `Math.h`.
- `Polyline.h` — header-only `Polyline2<T>` (aliases `Polyline2F`/`Polyline2D`): a plain 2D point-chain (`points` vector; segments are consecutive pairs), a domain-neutral geometric container like `Segment.h`. Implicitly constructible from a point vector so a sampled curve drops straight in. Key op: `findCrossings(other)` → ordered `Polyline2Crossing<T>` list (segment index on this polyline + intersection point), built on `Segment2::intersect`. `Vector.h`/`Segment.h`-only.
- `Segment.h` — header-only line-segment primitives: `Segment2<T>` (2D, `Vector2<T>`; aliases `Segment2F`/`Segment2D`/`Segment2I`) and `Segment3<T>` (3D, `Vector3<T>`; aliases `Segment3F`/`...`), both with public `start`/`end` fields. Shared: `getDir()`, `getLength()`/`getLengthSq()`, `getMidpoint()`, `pointAt(t)` (param in *distance* along the segment, not normalised — can go negative/past the end), `translate()`. `Segment2` also has the 2D-only `closestPointTo(p)` and `intersect(other)` (segment-segment crossing point or nullopt; parallel/collinear → no hit) — used by the app's road-network crossing/snapping. A plain geometric primitive like `Circle.h`/`Ray.h`, `Vector.h`-only.
- `StateMachine.h` — `IState` + `ITransition` based machine; `check()` walks transitions whose source matches the current state.
- `Property<T>` — clamped numeric value with min/max and `getValueRelative()`.
- `Window`, `Cursor`, `HandleMessages`, `Message` — thin Win32 wrappers (driven by `<Windows.h>` pulled in via `Common.h`).
- `Common.h` — the actual big-include header (Windows + STL). Pulled in via `stdafx.h` so every TU gets it for free through the PCH.

## Conventions worth matching

- Parameter naming: `i_` for in, `o_` for out, `a_` for accumulator/in-out, `d_` for data members, `s_` for statics. Stick to these when adding code.
- Two-space indentation, Allman braces, `namespace Sdk { ... } // ns Sdk` footer comment on the closing brace.
- Headers use `#pragma once`. Prefer including `SdkFwd.h` over full headers in other headers.
- Prefer the `CONTRACT_*` macros and `SAFE_DEREF` for error handling rather than ad-hoc checks.
- Because `TreatWarningAsError=true`, even `-Wsign-compare`-style warnings fail the build — clean them as you go.
