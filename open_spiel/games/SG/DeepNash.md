* 딥내쉬는 3가지로 이루어짐
1. R-Nad  
2. fine-tuning  
3. test-time improvement  

* R-Nad 는 3가지로 이루어져서 iteration 하며 fixed point(Nash E 지점) 까지 반복
1. Reward trasformation (보상값을 강화)
2. dynamic step (한 지점으로 수렴화)
3. 정책값 업데이트

* 선택가능 행동은 이동범위+공격범위  

* Observation
  1. 유닛 마다 2 Action
  2. 전장 테이블 크기 만큼 obs tensor 크기가 커진다. 이것은 문제다.
     1. ( obs 크기 = 전장 크기 ) 로 할 것이냐 ?
        이러면 obs 크기가 엄청 커진다. 
