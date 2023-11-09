//
// Created by alexs on 10/12/2023.
//

#ifndef FIRELIGHT_CORE_HPP
#define FIRELIGHT_CORE_HPP

#include "SDL2/SDL.h"
#include "coreoption.hpp"
#include "game.hpp"
#include "gamepad.hpp"
#include "input.hpp"
#include "libretro.h"
#include "video.hpp"
#include <iostream>
#include <vector>
#include <windows.h>

using std::array;
using std::string;
using std::vector;

namespace libretro {

typedef void (*RetroSetEnvironment)(bool (*)(unsigned cmd, void *data));
typedef void (*RetroSetVideoRefresh)(retro_video_refresh_t);
typedef void (*RetroSetAudioSample)(retro_audio_sample_t);
typedef void (*RetroSetAudioSampleBatch)(retro_audio_sample_batch_t);
typedef void (*RetroInputState)(retro_input_state_t);
typedef void (*RetroInputPoll)(retro_input_poll_t);
typedef void (*RetroRunFunc)();

class Core {

public:
  Gamepad *getGamepad(int port);
  void plugInGamepad(int port, Gamepad *gamepad);

  Video *getVideo();
  Input *getInput();

  std::basic_string<char> dumpJson();

  explicit Core(const std::string &libPath);

  virtual ~Core();

  bool handleEnvironmentCall(unsigned cmd, void *data);

  void init();

  void deinit();

  void reset();

  void run(double deltaTime);

  bool loadGame(Game *game);

  void setSystemDirectory(string);

  void setSaveDirectory(string);

private:
  array<Gamepad *, 8> gamepads = {nullptr};

  Video *video;
  Input *input;

  vector<string> environmentCalls;

  retro_system_info *retroSystemInfo;
  retro_system_av_info *retroSystemAVInfo;

  // Informational to frontend.
  bool canRunWithNoGame = false;
  unsigned performanceLevel = 0;
  bool supportsAchievements = false;
  bool shutdown = false;
  vector<retro_input_descriptor> inputDescriptors;

  // Informational to core.
  string systemDirectory;
  string coreAssetsDirectory;
  string saveDirectory;
  string libretroPath;
  string username;
  unsigned frontendLanguage;
  bool isJITCapable;

  retro_disk_control_callback *diskControlCallback;
  unsigned diskControlInterfaceVersion;
  retro_disk_control_ext_callback *diskControlExtCallback;
  retro_rumble_interface *rumbleInterface;
  uint64_t serializationQuirksBitmap;
  retro_vfs_interface_info *virtualFileSystemInterfaceInfo;
  retro_led_interface *ledInterface;
  unsigned messageInterfaceVersion;
  retro_message_ext *messageExt; // todo
  retro_fastforwarding_override *fastforwardingOverride;
  retro_system_content_info_override *contentInfoOverride;
  retro_game_info_ext *gameInfoExt;
  retro_throttle_state *throttleState;
  int saveStateContext;
  retro_microphone_interface *microphoneInterface;
  retro_netpacket_callback *netpacketCallback;
  retro_device_power *devicePower;
  bool fastforwarding;

  unsigned coreOptionsVersion;
  std::vector<CoreOption> options;

  retro_sensor_interface *sensorInterface;
  retro_camera_callback *cameraCallback;
  retro_log_callback *logCallback;
  retro_perf_callback *performanceCallback;
  retro_location_callback *locationCallback;
  retro_get_proc_address_interface *procAddressCallback;
  vector<retro_subsystem_info> subsystemInfo;
  vector<retro_memory_descriptor> memoryMaps;

  int audioVideoEnableBitmap;

  retro_audio_callback *audioCallback;
  unsigned minimumAudioLatency;
  retro_midi_interface *midiInterface;
  retro_audio_buffer_status_callback *audioBufferStatusCallback;

  unsigned numActiveInputDevices;
  bool supportsInputBitmasks;
  vector<retro_controller_description> controllerInfo;
  uint64_t inputDeviceCapabilitiesBitmask;
  retro_keyboard_callback *keyboardCallback;

  void recordPotentialAPIViolation(const string &msg);

  void *dll;

  void (*symRetroInit)();

  void (*symRetroDeinit)();

  unsigned (*symRetroApiVersion)();

  void (*symRetroGetSystemInfo)(retro_system_info *);

  void (*symRetroGetSystemAVInfo)(retro_system_av_info *);

  void (*symRetroSetControllerPortDevice)(unsigned, unsigned);

  void (*symRetroReset)();

  RetroRunFunc symRetroRun;

  size_t (*symRetroSerializeSize)();

  bool (*symRetroSerialize)(void *, size_t);

  bool (*symRetroUnserialize)(const void *, size_t);

  void (*symRetroCheatReset)();

  void (*symRetroCheatSet)(unsigned, bool, const char *);

  bool (*symRetroLoadGame)(const retro_game_info *);

  bool (*symRetroLoadGameSpecial)(unsigned, const retro_game_info *, size_t);

  void (*symRetroUnloadGame)();

  unsigned int (*symRetroGetRegion)();

  void *(*symRetroGetMemoryData)(unsigned);

  size_t (*symRetroGetMemoryDataSize)(unsigned);
};

} // namespace libretro

#endif // FIRELIGHT_CORE_HPP
