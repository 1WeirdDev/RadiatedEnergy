#pragma once

enum class LoadSceneMode{
    Single=0,
    Additive=1
};

#include "Scene.h"
class SceneManager{
public:
    static void Init();
    static void Shutdown();

    static void Update();
    static void Draw();
    
    /// @brief Allocates a new scene of TYPE and passes ARGS to it
    /// @tparam SCENE the Type to allocate
    /// @tparam ...ARGS The ARGS TO PASS TO TYPE contstructor
    /// @param mode LoadSceneMode enum
    /// @param ...args the args that get passed to constructor
    /// @return the pointer to the newly allocated scene
    template <typename SCENE, typename... ARGS>
    static SCENE* MakeScene(LoadSceneMode mode, ARGS&&... args){
        static_assert(std::is_base_of<Scene, SCENE>::value, "Must inherit Scene Class");
        if(mode == LoadSceneMode::Single){
            //Remove and cleanup scenes
            Shutdown();
        }
        SCENE* scene = new SCENE(args...);
        m_Scenes.push_back(scene);
        scene->Init();
        return scene;
    }

    /// @brief Attempts to remove any scene with the speciefied pointer
    /// @param scene the Scene* to search for
    /// @return returns true if success
    static bool RemoveScene(Scene* scene);
public:
    static std::vector<Scene*>& GetScenes() noexcept{return (std::vector<Scene*>&)m_Scenes;}
private:
    static std::vector<Scene*> m_Scenes;
};