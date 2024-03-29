# GameModule (Game Engine Prototype)
WinAPI에서 간단하게 게임을 만들 수 있도록 하기 위해 개발하고 있는 게임 모듈입니다.<br>
또한 게임 시스템에 대한 이해를 위해 공부 목적으로 개발하고 있습니다.

### Using Language
* C++

### Using Compiler
* VC++

### Using Naming Convention
* [Google Naming Convention](https://google.github.io/styleguide/cppguide.html#General_Naming_Rules)

### Using Graphic Library
* GDI, GDI+

### Using Sound Library
* ~~FMOD~~

### Life Cycle
* 업데이트 예정

### Developer Comment
* 기본적으로 GDI와 GDI+ 그래픽 라이브러리의 경우 특정 작업에서는 하드웨어 가속을 지원하지만 대부분의 작업을 CPU에서 처리합니다.
* GDI+는 GDI의 계량형이지만 그만큼 많은 기능을 제공하고 있기 때문에 상대적으로 처리 속도가 느립니다.<br>
때문에 5배에서 최대 10배까지의 속도 차이가 있을 수 있습니다.
* 처리 속도를 우선 시 한다면 GDI, 그래픽 품질을 우선 시 한다면 GDI+를 사용해 주세요.
* ~~WinAPI는 기본적으로 윈도우 메시지를 기반으로 동작을 하기 때문에 현재 구조상 윈도우 메시지 발생 시 게임 로직이 멈추게 됩니다.~~
* 해당 프로젝트는 텀프로젝트로 사용 후 Direct2D로 재개발 예정입니다.
* 재개발 시에는 MVP, MVVM, MVC 등의 디자인 패턴을 활용하여 관리의 용의성을 강화할 예정입니다.

![Honeycam 2022-11-29 21-25-23](https://user-images.githubusercontent.com/38973547/204528784-353df090-262c-4204-b3df-d89cf16d71c4.gif)
