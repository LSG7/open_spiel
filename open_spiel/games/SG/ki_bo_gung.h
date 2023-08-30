##ifndef OPEN_SPIEL_GAMES_KI_BO_GUNG
#define OPEN_SPIEL_GAMES_KI_BO_GUNG

/**
* @file ki_bo_gung.h
* @brief [기병 보병 궁병] '3가지 병' 으로 '두 플레이어' 가 싸우는 'inperfect information' 'zero sum' 게임 이다.
* 보병은 (창+방패) 팔랑크스 보병
* 턴베이스, 턴당 [이동,행동], 기병-보병-궁병 순으로, 동일 말에서 적군과의 순서는 랜덤으로, 
*
* 데미지 공식
* 기본으로 1 씩 데미지 주는 것으로 함.
* 공격 보너스 +1 : (보병 옆,뒤 <- 기병 돌격),
* 공격 패널티 -0.665 : (보병 <- 궁), (보병 전면 <- 기병 돌격)
* 반격 +1 : (보병 전면 <- 기병 돌격)
*
* @author SG Lee
* @date 8/30/2023
*/

/* observation 
 [0] 지형 정보             row * col

*/

// STD headers

// internal headers
#include "open_spiel/spiel.h"

namespace open_spiel {
namespace kbg {

inline constexpr int kNumPlayers = 2;
inline constexpr int kNumRows = 10;
inline constexpr int kNumCols = 10;

inline constexpr int kCellStates = TODO

inline constexpr int kFieldType = 3;  // 노멀, 숲, 장애물 
inline constexpr int kPieceType = 3;  // 기병, 보병, 궁수
inline constexpr int kNumCelss = kNumRows * kNumCols;
