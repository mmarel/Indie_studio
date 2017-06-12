#ifndef GUI_HPP
#define GUI_HPP

#include <map>
#include <vector>
#include <functional>
#include "../Common/Sprite.hpp"
#include "../Common/Component.hpp"
#include "../Interfaces/GameState.hpp"
#include "../Interfaces/IGUI.hpp"

namespace indie
{
    class GUI : public IGUI
    {
    private:
        std::vector<std::unique_ptr<indie::IComponent>>                                                _components;
        std::map<indie::GameState, std::function<std::vector<std::unique_ptr<indie::IComponent>> ()> > _loadComps;

        ///Load Components Functions
        std::vector<std::unique_ptr<indie::IComponent>>    loadMenu();
        std::vector<std::unique_ptr<indie::IComponent>>    loadSettings();
        std::vector<std::unique_ptr<indie::IComponent>>    loadScore();
        std::vector<std::unique_ptr<indie::IComponent>>    loadRoom(); ///Selection players etc..


        ///CreteComponent (*component params* + all paths to sprites)
        template <typename ... args>
        std::unique_ptr<indie::IComponent>   createComponent(size_t back_id, double x, double y,
                                                             double width, double height, indie::Color backColor,
                                                             indie::Color textColor, std::string text,
                                                             args... paths) {
            std::unique_ptr<indie::IComponent> res;
            indie::Sprite sprite(paths...);

            res = std::make_unique<indie::Component>(sprite, back_id, x, y, width, height, backColor, textColor, text);
            return (res);
        }

    public:
        GUI();
        virtual ~GUI(){}

        virtual std::size_t  size() const;
        virtual IComponent &at(std::size_t n);
        virtual void loadComponents(indie::GameState);
        virtual std::vector<std::unique_ptr<indie::ISprite> > getSprites();
    };
}

#endif