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
        std::vector<std::shared_ptr<indie::ISprite>>                                                   _sprites;
        std::vector<std::shared_ptr<indie::IComponent>>                                                _components;
        std::map<indie::GameState, std::function<std::vector<std::shared_ptr<indie::IComponent>> ()> > _loadComps;

        ///Load Components Functions
        std::vector<std::shared_ptr<indie::IComponent>>    loadMenu();
        std::vector<std::shared_ptr<indie::IComponent>>    loadSettings();
        std::vector<std::shared_ptr<indie::IComponent>>    loadScore();
        std::vector<std::shared_ptr<indie::IComponent>>    loadRoom(); ///Selection players etc..


        ///CreteComponent (*component params* + all paths to sprites)
        template <typename ... args>
        std::shared_ptr<indie::IComponent>   createComponent(size_t back_id, double x, double y,
                                                             double width, double height, indie::Color backColor,
                                                             indie::Color textColor, std::string text,
                                                             args... paths) {
            std::shared_ptr<indie::IComponent> res;
            std::shared_ptr<indie::Sprite> tmp;
            tmp = std::make_shared<indie::Sprite>(paths...);

            res = std::make_shared<indie::Component>(*tmp, back_id, x, y, width, height, backColor, textColor, text);
            _sprites.push_back(tmp);
            return (res);
        }

    public:
        GUI();
        virtual ~GUI(){}

        virtual std::size_t  size() const;
        virtual IComponent &at(std::size_t n) const;
        virtual void loadComponents(indie::GameState);
        virtual std::vector<std::shared_ptr<indie::ISprite> > getSprites();
    };
}

#endif