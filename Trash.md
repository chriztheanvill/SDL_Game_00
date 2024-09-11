# RenderSystem

- Usar cast (pointers)
    - Cambiarlo a usar variant

```c++
  SDL_Rect dst {};

  if (dynamic_cast<GraphicComponent::Tile*>(graphic.type.get()) != nullptr) {
    //      Tilemap || タイルマップ  (Tairu mappu)
    // Logger::Debug(LogType::Debug, "RenderSystem::Render tile ");
    dst = { static_cast<int>(transform.position.x * transform.scale.x),
            static_cast<int>(transform.position.y * transform.scale.y),
            static_cast<int>(graphic.src.w * transform.scale.x),
            static_cast<int>(graphic.src.h * transform.scale.y) };
  } else {
    //      sprite || スプライト (Supuraito)
    // Logger::Debug(LogType::Check, "RenderSystem::Render sprite ");
    dst = { static_cast<int>(transform.position.x),
            static_cast<int>(transform.position.y),
            static_cast<int>(graphic.src.w * transform.scale.x),
            static_cast<int>(graphic.src.h * transform.scale.y) };
  }
```

# GraphicComponent

```c++

   GraphicComponent(const GraphicComponent& gc) {
     // Logger::Debug(LogType::Check, "GraphicComponent copy constructor");
     // Logger::Debug(LogType::Check, "GraphicComponent copy constructor assetname: ",
     // gc.assetName);

     // if (gc.type.use_count() != 1)
     //   Logger::Debug(
     //     LogType::Check, "GraphicComponent copy constructor type count: ", gc.type.use_count()
     //   );

     // assert(
     //   gc.type.use_count() != 0
     //   || !fprintf(stderr, "GraphicComponent copy constructor: %s\n", gc.assetName.c_str())
     // );

     this->entityID = gc.entityID;
     this->assetName = gc.assetName;
     this->src = gc.src;
     this->zIndex = gc.zIndex;
     this->flip = gc.flip;
     // this->type.reset(gc.type.get());
     this->type = gc.type; // SharedPtr
   }
```