#ifndef OPEN_SPIEL_GAMES_KI_BO_GUNG_H_
#define OPEN_SPIEL_GAMES_KI_BO_GUNG_H_

/**
* @file ki_bo_gung.h
* @brief [기병 보병 궁병] '3가지 병' 으로 '두 플레이어' 가 싸우는 'inperfect information' 'zero sum' 게임 이다.
* 보병은 (창+방패) 팔랑크스 보병
* 턴베이스, 턴당 [이동,행동], 기병-보병-궁병 순으로, 동일 말에서 적군과의 순서는 랜덤으로, 
*
* [데미지 공식]
* 기본으로 1 씩 데미지 주는 것으로 함.
* 공격 보너스 +1 : (보병 옆,뒤 <- 기병 돌격),
* 공격 패널티 -0.665 : (보병 <- 궁), (보병 전면 <- 기병 돌격)
* 반격 +1 : (보병 전면 <- 기병 돌격)
*
* [Policy Head]
* deepnash 에서는 3+1=4 개 인데 (deployment, piece-selection, piece-displacemnt, value)
* 기보궁 게임에서는 배치X, 선택X, 이동(행동)O, 가치O,
* 즉 이동, 가치 2개 헤드만 있으면 된다.
* 이동과 행동을 분리해야하나? deepnash 는 하나인데
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
#include "baseT.h"

namespace open_spiel {
namespace kbg {

class kbgGame : public baseT::baseTGame {
 public:
  explicit kbgGame(const GameParameters& params);
  virtual ~kbgGame();
  std::unique_ptr<State> NewInitialState() const override;

 protected:

 private:

};

class kbgState : public baseT::baseTState {
 public:
  kbgState(std::shared_ptr<const Game> game);
  kbgState(const kbgState&) = default;
  virtual ~kbgState();
  kbgState& operator=(const kbgState&) = default;

  void init_map() override;
  void init_unit() override;

 protected:

 private:

};

} // kbg
} // open_spiel

#endif // OPEN_SPIEL_GAMES_KI_BO_GUNG_H_