# Ground Rule  
  * 정형화 시켜서 재사용 원활히
  * 순차적 주석으로 로직 심플&이해쉽게
  * 확장성. 나중에 대규모로 확장 가능하게.
  * 관련 앱과 데이터 호환 용이
  * 학습에 사용하기 용이

# TODO
 1. 하나의 게임에서 self-play 로 trajectory 를 2개 만들어야 한다.
 어차피 상대방 역할 해주는 봇도 있어야 하는데 
 그 봇도 똑똑해야 하고
 하는김에 궤적 하나 더 만드는게 효율성 좋으니  


 2. joint action 으로 만들어야 한다.
 한번은 이동하고 한번은 행동하고
 deepnash 는 선택,행동 이었다면 나는 이동,행동 이다.

 # 일기
23.8.30 
게임 생성 시작  

* 셀은 vector [z][y][x], map_coord 로 접근  
* 유닛은 vector [id], unique unit_id 로 접근  
0 번 player 는 1번부터 시작. 접근할 때 (p0_id) 으로 접근  
1 번 player 는 1001번부터 시작. 접근할 때 (p1_id - 1000) 으로 접근  

23.10.10
보드 표현 규정
* [빈땅은 '_ '] 스페이스는 유닛 개수에 따라 변동적  
* [유닛은 'player_id + unit_id] ex=[01]  

23.10.12
* 수동빌드 할 때 BUILD_TYPE=Debug 해줘야 -g 옵션 들어감
* games/ 아래에서 CMakeLists.txt 에서 빌드해줘야 실행 파일에 디버그 들어가서 같이 빌드됨

* Interger Encoding vs One-hot Encoding
https://medium.com/geekculture/machine-learning-one-hot-encoding-vs-integer-encoding-f180eb831cf1  

* 유닛 위치의 Z축 = 채널 에 병종을 one-hot, 체력, 공격력, 방어력 표현   
* Mac 에는 gdb 가 없다. lldb 써야 한다.  
* Mac 에서 vs code 에다가 codeLLDB 깔면 연결된다. F5 로 디버깅 실행