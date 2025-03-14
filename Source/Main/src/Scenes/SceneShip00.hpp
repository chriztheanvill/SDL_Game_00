//
// Created by cris on 12/29/24.
//

#ifndef SCENESHIP00_HPP
#define SCENESHIP00_HPP

#include "SceneBase.hpp"

class SceneShip00 : public SceneBase {
public:
    SceneShip00() ;
    ~SceneShip00() ;

    auto Enter() -> void override;
    auto Exit() -> void override;
    auto Update(float deltaTime) -> void override;
};



#endif //SCENESHIP00_HPP