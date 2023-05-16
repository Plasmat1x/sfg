namespace c1
{
    //base class
    class Command
    {
    public:
        virtual ~Command() {}
        virtual void execute() = 0;
    };

    class JumpCommand : public Command
    {
    public:
        virtual void execute()
        {
            //jump();
        }
    };

    class RollCommand : public Command
    {
    public:
        virtual void execute()
        {
            //roll();
        }
    };

    class InputHandler
    {
    public:
        void handleInput()
        {
            if (true /*sf::Keyboard::isKeyPressed(sf::Keyboard::<Key>)*/)
            {
                //A1->execute();
            }//else if ...
        }

    private:
        Command* A1;
        Command* A2;
        Command* A3;
        Command* A4;
    };
} // namespace c1

namespace c2
{
    class GameActor;

    class Command
    {
    public:
        virtual ~Command() {}
        virtual void execute(GameActor& actor) = 0;
    };

    class JumpCommand : public Command
    {
    public:
        virtual void execute(GameActor& actor)
        {
            //actor.jump;
        }
    };

    class InputHandler//as c1
    {
    public:
        Command* HandleInput()
        {
            if (true /*isPressed(<Key>)*/) return A1;
            //else if ...

            return nullptr;
        }

    private:
        Command* A1;
    };

    void SomeFnc()
    {
        Command* command = nullptr; // = inputHandler.handleInput();
        if (command)
        {
            //command->execute(actor);
        }
    }

} // namespace c2



