/** @file AudioManager.hpp
 * Allow playing and mixing of game sounds and musics.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_AUDIO_MANAGER_HPP
#define HPP_AUDIO_MANAGER_HPP

namespace AudioManager
{
	/** All available sounds. */
	typedef enum
	{
		SOUND_ID_AMMUNITION_TAKEN,
		SOUND_ID_PLAYER_FIRESHOT,
		SOUND_ID_PLAYER_FIRESHOT_MORTAR_SHELL,
		SOUND_ID_PLAYER_MORTAR_SHELL_RELOADING,
		SOUND_ID_PLAYER_HEALED,
		SOUND_ID_PLAYER_LIFE_INCREASED,
		SOUND_ID_SMALL_ENEMY_FIRESHOT,
		SOUND_ID_MEDIUM_ENEMY_FIRESHOT,
		SOUND_ID_BIG_ENEMY_FIRESHOT,
		SOUND_ID_ENEMY_BULLET_IMPACT,
		SOUND_ID_SMALL_ENEMY_EXPLOSION,
		SOUND_ID_MEDIUM_ENEMY_EXPLOSION,
		SOUND_ID_BIG_ENEMY_EXPLOSION,
		SOUND_ID_ENEMY_SPAWNER_BULLET_IMPACT,
		SOUND_ID_ENEMY_SPAWNER_EXPLOSION,
		SOUND_ID_MENU_MOVE,
		SOUND_ID_MENU_SELECT,
		SOUND_ID_MACHINE_GUN_TAKEN,
		SOUND_ID_BULLETPROOF_VEST_TAKEN,
		SOUND_ID_NO_SOUND, //!< Playing this sound ID results in no sound being played
		SOUND_IDS_COUNT
	} SoundId;

	/** Load all game sounds.
	 * @return 0 if all files were successfully loaded,
	 * @return -1 if an error occurred.
	 */
	int initialize();

	/** Free all allocated resources. */
	void uninitialize();

	/** Play the specified sound once.
	 * @param id Which sound to play.
	 * @param soundSourceAngle Clockwise-oriented angle between sound emitter and game camera (which is screen center). Angle is an integer value between 0 and 359. Here are some notable angle values : 0 is directly in front, 90 is directly to the right, 180 is directly behind and 270 is directly to the left.
	 * @param soundSourceDistance Distance between sound emitter and game camera. This is an integer number between 0 and 255. Value 0 is the nearest one, value 255 is the farthest (but player can still hear it).
	 * @note Letting default values to soundSourceAngle and soundSourceDistance disables 3D sound effect.
	 */
	void playSound(SoundId id, int soundSourceAngle = 0, int soundSourceDistance = 0);

	/** Start playing randomly all available musics. */
	void playMusic();

	/** Pause or resume music playing.
	 * @param isMusicPaused Set to 1 to pause music, set to 0 to resume playing.
	 */
	void pauseMusic(bool isMusicPaused);

	/** Immediately stop all channels. */
	void stopAllSounds();

	/** Compute and object distance and angle from camera center.
	 * @param objectCenterX Object center X coordinate, in map coordinates.
	 * @param objectCenterY Object center Y coordinate, in map coordinates.
	 * @param pointerAngle On output, contain an angle between 0 and 359 degrees. See AudioManager::playSound() for more information.
	 * @param pointerDistance On output, contain a distance between 0 and 255. See AudioManager::playSound() for more information.
	 */
	void computePositionFromCamera(int objectCenterX, int objectCenterY, int *pointerAngle, int *pointerDistance);
}

#endif
