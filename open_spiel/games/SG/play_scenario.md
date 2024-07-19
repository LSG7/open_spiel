0. 맵 초기화, 유닛 배치
```
    init_first -> init_map,init_unit
```
Player 별 돌아가며 다음을 한턴 안에 수행 함.
1. Observation String 생성 (유저에게 보여주기 위함), Obseravation | Information Tensor 준비 (매 액션마다 갱신하는 방법 사용)
2. inference network or random select(개발중 사용) 
3. 액션 선택 (action_select_tile)

턴 넘김
