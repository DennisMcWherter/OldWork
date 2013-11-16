#include "include/Sound.h"

void Sound::PlaySound(irrklang::ISoundEngine *_engine)
{
	_snd = _engine->play2D("Data/Sounds/sound01.wav", true, false, false); 

 
 if (_snd)
     _snd->setVolume(0.2f);
 
 
}
void Sound::drop()
{
	if(_snd)
	_snd->drop();
}