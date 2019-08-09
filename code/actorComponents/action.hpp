#ifndef c_action_hpp
#define c_action_hpp

class c_actor;

class c_action
{
    private:
        c_actor* father;
        bool active;
        int duration;
        int energy;
        structEventData eventData;
        
    public:
        c_action(c_actor* father);
        bool isRunning();
        bool start(const structEventData& eventData);
        void timeUpdate();
};

#endif
