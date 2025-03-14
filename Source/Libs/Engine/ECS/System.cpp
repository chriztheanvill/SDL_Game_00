//
//  Created by cris on 8/13/24.
//

#include "System.hpp"
#include "./Entity.hpp"

// auto System::Hello(uint64_t id) -> uint64_t { return m_entities.at(id)->GetID(); }

auto System::AddEntity(const Entity& entity) -> void {
  assert(!entity.GetName().empty() || !fprintf(stderr, "No name in this entity\n"));
  m_entities.emplace_back(entity);
}

auto System::GetEntity(uint64_t id) -> Entity& {
  // auto it = std::ranges::find_if(m_entities,
  // [id](Entity& entity) { return entity.GetID() == id; // });
  // assert(it != m_entities.end() || !fprintf(stderr, "\nEntity not found  \n"));
  // return *it;
  return *std::ranges::find_if(m_entities, [id](Entity& entity) { return entity.GetID() == id; });
}

auto System::RemoveEntity(uint64_t entityID) -> void {
  // auto System::RemoveEntity(std::shared_ptr<Entity>& entity) -> void {
  // Busca todos los elementos, elimina los que esten vacios
  // for (auto& eachEntity: m_entities) {
  //   if (eachEntity->GetName().empty()) {
  //     // Logger::Debug(
  //     //   LogType::Check_01,
  //     //   "System::RemoveEntity: id: ",
  //     //   eachEntity.get().GetID(),
  //     //   " - Name: ",
  //     //   eachEntity.get().GetName()
  //     // );
  //
  //
  //
  //     // std::erase(
  //     //   m_entities, std::ranges::find(m_entities, eachEntity.get().GetID(),
  //     //   &Entity::GetID)->get()
  //     // );
  //     // auto [start, end] { std::ranges::remove(m_entities, entity) };
  //     // auto [start, end] {
  //     //   std::ranges::remove(m_entities, *std::ranges::find(m_entities, entity.GetID(),
  //     //   &Entity::GetID))
  //     // };
  //     // std::ranges::remove_if(m_data, [&](const auto& val) { return val.entityID != id; })
  //     // m_entities.erase(start, end);
  //   }
  // }

  // Este solo busca por id, pero al eliminar un elemento, el id no se actualiza
  auto [start, end] { std::ranges::remove(m_entities, entityID, &Entity::GetID) };

  // auto [start, end] { std::ranges::remove(m_entities, entity->GetID(), &Entity::GetID) };

  // Este busca por nombre, si esta vacio, lo elimina
  // auto [start, end] { std::ranges::remove_if(m_entities, [&](const auto& val) {
  //   return val->GetName().empty();
  // }) };

  m_entities.erase(start, end);

  // std::erase(m_entities, entity);
  // Busca el ultimo elemento y lo elimina si esta vacio
  // auto r = m_entities.at(m_entities.size() - 1);
  // if (r.get().GetName().empty()) {
  //   //
  //   Logger::Debug(
  //     LogType::Log, "System::RemoveEntity: id: ", r.get().GetID(), " - Name: ", r.get().GetName()
  //   );
  //   m_entities.pop_back();
  //   //
  // }

  // m_entities.erase(
  //   std::find_if(
  //     m_entities.begin(),
  //     m_entities.end(),
  //     [entity](const std::reference_wrapper<Entity>& ref) {
  //   return ref.get().GetID() == entity.GetID();
  // }
  //   )
  // );

  // auto it = std::find(m_entities.begin(), m_entities.end(), entity);
  // if (it != m_entities.end()) { m_entities.erase(it); }

  // m_entities.pop_back();
  // std::erase(m_entities, *std::ranges::find(m_entities, entity.GetID(), &Entity::GetID));
  // auto [start, end] { std::ranges::remove(m_entities, entity) };
  // auto [start, end] {
  //   std::ranges::remove(m_entities, *std::ranges::find(m_entities, entity.GetID(),
  //   &Entity::GetID))
  // };
  // std::ranges::remove_if(m_data, [&](const auto& val) { return val.entityID != id; })
  // m_entities.erase(start, end);

  // auto [start, end] { std::ranges::remove(m_entities, *std::ranges::find(m_entities,
  // entity.GetID(), &Entity::GetID))) }; std::ranges::remove_if(m_data, [&](const auto& val) {
  // return val.entityID != id; }) m_entities.erase(start, end);
}

auto System::GetEntities() -> std::vector<Entity>& { return m_entities; }

auto System::GetSignature() const -> const Signature& { return m_componentSignature; }