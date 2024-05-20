# Env
* source env_sg.sh (환경변수)  
* source venv/bin/activate  

빌드 방법 두가지.
1. open spiel 에서 제공하는 방법. clang 을 쓴다.  
  ./build_sg.sh
2. 내가 만든 방법. gcc clang 중에 골라 쓴다. gcc,clang 선택은 env_sg.sh 에서.  
  cd build_sg 
  ./set_cmake_manual.sh
  make -j8 kbg_test



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

* 채널에 셀의 정보를 나열하고 Unet 으로 셀의 정보를 분석해야 한다.
* 셀이 z 축으로 쌓여도 되나? 
* action id 를 셀 번호로 해야 한다. 근데 셀이 존나 많다.

* 관찰, 생각, 행동

23.10.31
* 혼합 정밀도를 사용해야 한다. 인풋은 float, 연산은 bf16, 아웃은 ?
* obs 를 1D vector 로 만든다. pythoh 에서 이것을 asarray() 하고 reshape() 한다. 

23.11.6
* apple M3 에서는 bf16 지원한다고 하나 apple coreML 문서에는 float16 지원하는 것만 설명되어 있다.
그러니 지금은 일단 float16 으로 만든다.
* C++23 부터 float16_t bfloat16_t 존재. c++23 으로 빌드.
* gcc g++13 깔아야함. developernote.com/2023/08/installing-gcc13-on-ubuntu-22-04
* clang++17 깔아야함. clang 은 STDCPP_FLOAT16_T 지원안해서 못씀. c++23 정식지원까지 사용중지.
* Mac 에서도 gcc 써야함.