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
  
  --------------------------------------
  
  // Ok
   std::ranges::sort(GetEntities() | std::ranges::views::drop_while([&](const Entity& lhs) {
     return !lhs.GetComponent<GraphicComponent>().YSort;
   }));

   auto r = std::ranges::partition(GetEntities(), [](const Entity& lhs) {
     return lhs.GetComponent<GraphicComponent>().zIndex > 0;
   });

   std::ranges::sort(
     GetEntities() | std::ranges::views::drop_while([](const Entity& lhs) {
     auto r = lhs.GetComponent<GraphicComponent>().YSort;
     Logger::Debug(LogType::Debug, "--- Sorting entities lambdas lhs: ", lhs.GetName(), " - r: ",
     r); return r;
   }),
     [](const Entity& lhs, const Entity& rhs) {
     // Logger::Debug(LogType::Debug, "Sorting entities lhs: ", lhs.GetName());
     // Logger::Debug(LogType::Debug, "Sorting entities rhs: ", rhs.GetName());

     auto ltr = lhs.GetComponent<TransformComponent>();
     auto rtr = rhs.GetComponent<TransformComponent>();

     return ltr.position.y < rtr.position.y;
   }
   );

   Logger::Debug(LogType::Debug, "Sorting: ", entity.GetName());
   for (size_t i {}; i < GetEntities().size(); i++) {
     Entity& a = GetEntities()[i];

     if (auto& b = GetEntities()[i + 1]; &b != nullptr) {
       Logger::Debug(LogType::Debug, "-- Sorting: ", b.GetName());
     }
   }
     // Logger::Debug(LogType::Debug, "Sorting: ", entity.GetName());

   for (auto i = GetEntities().begin(); i != GetEntities().end(); i++) {
     if (!i.base()->GetComponent<GraphicComponent>().YSort) continue;
     Entity& a = *i;
     float ay = a.GetComponent<TransformComponent>().position.y;

     if (auto b = i + 1; b != GetEntities().end()) {
       if (!b.base()->GetComponent<GraphicComponent>().YSort) { continue; }
       Logger::Debug(LogType::Debug, "-- Sorting: ", b.base()->GetName());

       float by = b.base()->GetComponent<TransformComponent>().position.y;
     }
     // Entity& a = entities[i];

     // auto graph = entities[i].GetComponent<GraphicComponent>();
     // if(graph.YSort)
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