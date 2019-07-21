#define GAME_STATE_NORMAL_GAMEPLAY                    0x00 // Normal gameplay
#define GAME_STATE_DEAD                               0x01 // Dead?
#define GAME_STATE_RESET_TO_CHECKPOINT                0x02 // Reset to checkpoint
#define GAME_STATE_PRE_DYING                          0x03 // Pre dying
#define GAME_STATE_DYING_ANIMATION                    0x04 // Dying animation
#define GAME_STATE_EXPLOSION_SCORE_COUNTING_DOWN      0x05 // Explosion/Score counting down
#define GAME_STATE_END_OF_LEVEL                       0x06 // End of level
#define GAME_STATE_END_OF_LEVEL_GATE_MUSIC            0x07 // End of level gate, music
#define GAME_STATE_INCREMENT_LEVEL                    0x08 // Increment Level, load tiles
#define GAME_STATE_GOING_DOWN_A_PIPE                  0x09 // Going down a pipe
#define GAME_STATE_WARPING_TO_UNDERGROUND             0x0A // Warping to underground?
#define GAME_STATE_GOING_RIGHT_IN_A_PIPE              0x0B // Going right in a pipe
#define GAME_STATE_GOING_UP_OUT_OF_A_PIPE             0x0C // Going up out of a pipe
#define GAME_STATE_AUTO_SCROLLING_LEVEL               0x0D // Auto scrolling level
#define GAME_STATE_INIT_MENU                          0x0E // Init menu
#define GAME_STATE_START_MENU                         0x0F // Start menu
#define GAME_STATE_LEVEL_START                        0x11 // Level start
#define GAME_STATE_GO_TO_BONUS_GAME                   0x12 // Go to Bonus game
#define GAME_STATE_ENTERING_BONUS_GAME                0x13 // Entering Bonus game
#define GAME_STATE_SETUP_MARIO_SPRITE                 0x14 // Setup Mario sprite
#define GAME_STATE_BONUS_GAME                         0x15 // Bonus game
#define GAME_STATE_MOVE_THE_LADDER                    0x16 // Move the ladder
#define GAME_STATE_BONUS_GAME_WALKING                 0x17 // Bonus game walking
#define GAME_STATE_BONUS_GAME_DESCENDING_LADDER       0x18 // Bonus game descending ladder
#define GAME_STATE_BONUS_GAME_ASCENDING_LADDER        0x19 // Bonus game ascending ladder
#define GAME_STATE_GETTING_PRICE                      0x1A // Getting price
#define GAME_STATE_LEAVING_BONUS_GAME                 0x1B // Leaving Bonus game
#define GAME_STATE_SMTH_WITH_THE_GATE_AFTER_A_BOSS    0x1C // Smth with the gate after a boss
#define GAME_STATE_GATE_OPENING                       0x1E // Gate opening
#define GAME_STATE_GATE_OPEN                          0x1F // Gate open
#define GAME_STATE_WALK_OFF_BUTTON                    0x20 // Walk off button
#define GAME_STATE_MARIO_OFFSCREEN                    0x21 // Mario offscreen
#define GAME_STATE_SCROLL_TO_FAKE_DAISY               0x22 // Scroll to fake Daisy
#define GAME_STATE_WALK_TO_FAKE_DAISY                 0x23 // Walk to fake Daisy
#define GAME_STATE_FAKE_DAISY_SPEAK                   0x24 // Fake Daisy speak
#define GAME_STATE_FAKE_DAISY_MORPHING                0x25 // Fake Daisy morphing
#define GAME_STATE_FAKE_DAISY_MONSTER_JUMPING_AWAY    0x26 // Fake Daisy monster jumping away
#define GAME_STATE_TATANGA_DYING                      0x27 // Tatanga dying
#define GAME_STATE_TATANGA_DEAD_PLANE_MOVES_FORWARD   0x28 // Tatanga dead, plane moves forward
#define GAME_STATE_DAISY_SPEAKING                     0x2A // Daisy speaking
#define GAME_STATE_DAISY_MOVING                       0x2B // Daisy moving
#define GAME_STATE_DAISY_KISSING                      0x2C // Daisy kissing
#define GAME_STATE_DAISY_QUEST_OVER                   0x2D // Daisy quest over
#define GAME_STATE_MARIO_CREDITS_RUNNING              0x2E // Mario credits running
#define GAME_STATE_ENTERING_AIRPLANE                  0x2F // Entering airplane
#define GAME_STATE_AIRPLANE_TAKING_OFF                0x30 // Airplane taking off
#define GAME_STATE_AIRPLANE_MOVING_FORWARD            0x31 // Airplane moving forward
#define GAME_STATE_AIRPLANE_LEAVING_HANGER            0x32 // Airplane leaving hanger?
#define GAME_STATE_IN_BETWEEN_TWO_CREDITS             0x33 // In between two credits?
#define GAME_STATE_CREDITS_COMING_UP                  0x34 // Credits coming up
#define GAME_STATE_CREDITS_STAND_STILL                0x35 // Credits stand still
#define GAME_STATE_CREDITS_LEAVE                      0x36 // Credits leave
#define GAME_STATE_AIRPLANE_LEAVING                   0x37 // Airplane leaving
#define GAME_STATE_THE_END_LETTERS_FLYING             0x38 // THE END letters flying
#define GAME_STATE_PRE_GAME_OVER                      0x39 // Pre game over?
#define GAME_STATE_GAME_OVER                          0x3A // Game over
#define GAME_STATE_PRE_TIME_UP                        0x3B // Pre time up
#define GAME_STATE_TIME_UP                            0x3C // Time
