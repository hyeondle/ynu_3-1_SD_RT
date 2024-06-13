# ynu_3-1_SD_RT
ynu 3-1 Software_design's subject. __ My little Ray-Tracer w/ mlx

env
:
MacOS

how to run
:
type

"make run"

in root directory

implemented
:
simple phong model (binary color)

diffuse rendering model (can define reflect depth, sample pixel amount)

moving camera as normal coordinate system (x y z)

material


not implemented
:
multiple color phong model

texture adaption

moving camera as cam coordinate system (yaw roll pitch)

map parser

#how to run

맥 운영체제에서 실행 가능합니다.

프로젝트의 루트 디렉토리에서 make 입력시 실행 가능합니다. (Makefile이 있는 위치)

##현재 조작 가능한 변수 :

1) s,w a,d q,e : 앞 뒤 왼쪽 오른쪽 위 아래 카메라 이동 (간이 phong_model 고정)

2) t, y : 현재 화면을 간이 phong_model에서 diffuse model로 렌더링합니다. (30초 이상 소요) t : 고화질, y : 최 저화질 (반사 2번, 한 픽셀당 샘플링 1번)

##현재 수정 가능한 변수 :

1) MlxBase.hpp 에서 매크로 WIDTH 수정 시 화면의 가로 크기를 늘릴 수 있습니다. (현재 480, 종횡비는 16:9)

2) MlxBase.cpp 에서 int Mlx::press_event(int keycode, void *param) 함수의 내부 변수 cam->samples_per_pixel, cam->max_depth를 증가시킴으로서 분산 모델의 렌더링 퀄리티 및 반사 깊이가 조절이 가능합니다.

3) 물체 추가 방법은 main.cpp에서 make_shared<물질매채>(인자) 로 shared_ptr을 생성 후, 원하는 물체를 hittable_list world; 변수 아래에 world.add(make_shared<물체형태>(인자))로 주면 됩니다.

#구현 정도가 부족한 이유

혼자서 나머지 기능들 (not implemented)을 추가로 구현하고 수식의 계산을 마저 하기에는 시간적으로 도저히 기한에 맞출 수 없고, 프로젝트의 규모도 너무나도 커지며, 혼자서 감당할 수 있는 양이 아니라고 판단했습니다. 하나의 추가적인 조명 처리 혹은 텍스쳐 처리같은 기능을 추가할 때 마다 모든 클래스를 하나씩 수정해야 하는 경우가 발생할 때도 있고, 수식의 계산 및 이해를 위해 학교에서 배운 내용 이상의 수학적 지식을 요구하는 경우도 있어 최대한 초기 목적인 phong_model의 예시와 분산 조명 처리 방식에 대해서 우선적으로 적용하는 것을 목표로 하였습니다.
