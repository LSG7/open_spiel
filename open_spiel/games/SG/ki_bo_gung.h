##ifndef OPEN_SPIEL_GAMES_KI_BO_GUNG
#define OPEN_SPIEL_GAMES_KI_BO_GUNG

/**
* @file ki_bo_gung.h
* @brief [기병 보병 궁병] '3가지 병' 으로 '두 플레이어' 가 싸우는 'inperfect information' 'zero sum' 게임 이다.
* @author SG Lee
* @date 8/30/2023
*/

// STD headers

// internal headers
#include "open_spiel/spiel.h"

namespace open_spiel {
namespace kbg {

inline constexpr int kNumPlayers = 2;
inline constexpr int kNumRows = 10;
inline constexpr int kNumCols = 10;
inline constexpr int kNumCelss = kNumRows * kNumCols;
inline constexpr int kCellStates = TODO
