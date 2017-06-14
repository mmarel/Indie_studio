#ifndef GAME_HPP
# define GAME_HPP

# include "Interfaces/Sound.hpp"
# include "Graphical/Model.hpp"
# include "Game/Load.hpp"
# include "Game/Scene.hpp"
# include "Game/Map.hpp"
# include "Game/Settings.hpp"
# include "Interfaces/IGame.hpp"
# include "Common/GUI.hpp"
# include <map>

namespace indie {
  # define PLAYER_SPEED 0.2
  typedef std::function<void()>                                               TurnHandler;
  typedef std::function<void(const std::size_t &, const std::size_t &)>       TileHandler;

  class Game : public indie::IGame {
    public:
      Game();
      virtual ~Game();

    public:
      // Getters for ressources to load
      virtual std::unique_ptr<std::vector<std::unique_ptr<indie::ISprite> > >     getSpritesToLoad() const;
      virtual std::unique_ptr<std::vector<std::unique_ptr<IModel> > >             getModelsToLoad() const;
      virtual std::unique_ptr<std::vector<std::pair<std::string, SoundType> > >   getSoundsToLoad() const;
      virtual std::unique_ptr<std::vector<std::unique_ptr<indie::IScene> > >      getScenesToLoad() const;

    public:
      virtual void notifyEvent(std::vector<Event> &&events);

    private:
      void  handleEvents();
      void  move_left(indie::Player &);
      void  move_right(indie::Player &);
      void  move_down(indie::Player &);
      void  move_up(indie::Player &);
      void  bomb(indie::Player &);

      // --- Process Part - Start
    public:
      virtual void process();

    private:
      void  menuProcess();
      void  splashScreen();
      void  gameProcess();
      void  quit();

    private:
      // Tile Handlers
      void  handleBomb(const std::size_t &,
                        const std::size_t &);
      void  handlePlayer(const std::size_t &,
                          const std::size_t &,
                          int);

    private:
      void spreadBombAnimation(const std::size_t &,
                                const std::size_t &,
                                const std::size_t &,
                                const std::size_t &);
      void spreadBombAnimationLine(const std::size_t &,
                                    const std::size_t &,
                                    const std::size_t &);
      void spreadBombAnimationCol(const std::size_t &,
                                  const std::size_t &,
                                  const std::size_t &);
    public:
      virtual GameState                 getGameState() const;
      virtual const IMap                &getCurrentMap() const = 0;
      virtual const std::vector<size_t> &getObjectsId() const;
      virtual const IGUI                &getGUI() const = 0;
      virtual const std::vector<Sound>  &getSoundsToPlay() const = 0;

    private:
      std::vector<indie::Sound> _sounds;
      GameState               _gameState;
      std::vector<Event>      _events;
      Map                     _map;
      GUI                     _gui;
      Settings                _settings;
  };
};

#endif /* GAME_HPP */
