#ifndef c_sound_hpp
#define c_sound_hpp

class c_sound
{
	private:
		sf::Music ambience;
		float ambienceVol;

	public:
		c_sound() {}
		void update();
        void playAmbience(std::string track);
};

#endif