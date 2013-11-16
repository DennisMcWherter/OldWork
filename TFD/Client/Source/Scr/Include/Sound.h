#ifndef SOUND_INCLUDED
#define SOUND_INCLUDED

#include <irrKlang.h>




class Sound
{
public: Sound() {};
		~Sound() {};


		void PlaySound(irrklang::ISoundEngine *engine);


		void drop();
private:
irrklang::ISound* _snd;


};

#endif //SOUND_INCLUDED