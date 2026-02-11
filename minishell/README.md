# 🐚 Minishell

![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)
![Build](https://img.shields.io/badge/Build-Makefile-green?style=for-the-badge&logo=gnu-make)
![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux-lightgrey?style=for-the-badge&logo=linux)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

<br />

<p align="center">
  <strong>Bash 쉘을 모방한 나만의 쉘 프로그램</strong>
  <br />
  프로세스 제어, 파일 디스크립터 관리, 시그널 핸들링 등 리눅스 시스템 프로그래밍의 핵심 개념을 학습하고 구현한 프로젝트입니다.
</p>

<br />

## 목차 (Table of Contents)

- [개요 (About The Project)](#-개요-about-the-project)
- [주요 기능 (Key Features)](#-주요-기능-key-features)
- [디렉토리 구조 (Directory Structure)](#-디렉토리-구조-directory-structure)
- [설치 및 실행 (Installation & Usage)](#-설치-및-실행-installation--usage)
- [구현 상세 (Implementation Details)](#-구현-상세-implementation-details)
- [저자 (Authors)](#-저자-authors)

<br />

## 📖 개요 (About The Project)

**Minishell**은 C언어를 사용하여 Bash 쉘의 동작을 모방하여 만든 쉘 프로그램입니다. 
명령어를 파싱하고, 프로세스를 생성하여 실행하며, 파이프와 리다이렉션을 통해 데이터 흐름을 제어합니다.

이 프로젝트를 통해 다음과 같은 시스템 프로그래밍 역량을 길렀습니다:
- **프로세스 관리**: `fork`, `execve`, `waitpid` 등을 이용한 자식 프로세스 생성 및 관리
- **파일 I/O**: `dup2`, `pipe`를 이용한 표준 입출력 제어 및 파이프라인 구축
- **시그널 처리**: `sigaction`을 이용한 시그널(SIGINT, SIGQUIT 등) 커스텀 핸들링
- **메모리 관리**: 동적 할당 및 해제를 통한 메모리 누수 방지

<br />

## ✨ 주요 기능 (Key Features)

### 1. 명령어 실행 (Command Execution)
- 절대 경로, 상대 경로, 환경 변수 `PATH`를 통한 명령어 실행
- 따옴표 (`'`, `"`) 처리 및 환경 변수(`$USER`, `$?` 등) 확장

### 2. 리다이렉션 & 파이프 (Redirection & Pipes)
- `<`: 입력 리다이렉션
- `>`: 출력 리다이렉션 (덮어쓰기)
- `>>`: 출력 리다이렉션 (이어쓰기)
- `<<`: 히어닥 (Here-document)
- `|`: 파이프라인 (다중 파이프 지원)

### 3. 빌트인 명령어 (Built-in Commands)
별도의 프로세스 생성 없이 쉘 내부에서 실행되는 명령어:
| 명령어 | 설명 | 옵션 |
|:---:|---|:---:|
| `echo` | 인자 출력 | `-n` |
| `cd` | 디렉토리 이동 | - |
| `pwd` | 현재 경로 출력 | - |
| `export` | 환경 변수 설정 | - |
| `unset` | 환경 변수 해제 | - |
| `env` | 환경 변수 목록 출력 | - |
| `exit` | 쉘 종료 | status code |

### 4. 시그널 핸들링 (Signal Handling)
- `Ctrl-C` (SIGINT): 새로운 프롬프트 출력
- `Ctrl-D` (EOF): 쉘 종료
- `Ctrl-\` (SIGQUIT): 무시 (자식 프로세스에서는 동작)

<br />

## 📂 디렉토리 구조 (Directory Structure)

```bash
minishell
├── inc/               # 헤더 파일 (minishell.h)
├── src/               # 소스 코드
│   ├── builtins/      # 빌트인 명령어 구현 (cd, echo, exit 등)
│   ├── command/       # 명령어 실행 및 파이프/리다이렉션 처리
│   ├── tokenizer/     # 렉서 및 파서 (토큰화, 구문 분석)
│   ├── utils/         # 유틸리티 함수 (에러 처리, 환경 변수 등)
│   ├── main.c         # 메인 진입점 (REPL 루프)
│   ├── parser_handler.c
│   └── signal_handler.c
├── libft/             # 커스텀 라이브러리 (Libft)
└── Makefile           # 빌드 스크립트
```

<br />

## 🚀 설치 및 실행 (Installation & Usage)

### 사전 요구 사항 (Prerequisites)
- gcc 또는 clang 컴파일러
- make 유틸리티
- readline 라이브러리

### 빌드 (Build)
```bash
# 레포지토리 클론
git clone <repository_url> minishell

# 디렉토리 이동
cd minishell/minishell

# 컴파일
make
```

### 실행 (Run)
```bash
./minishell
```

### 테스트 예시 (Examples)
```bash
minishell$ ls -l | grep "Makefile" > result.txt
minishell$ cat < result.txt
minishell$ echo "Hello $USER"
```

<br />

## 🛠 구현 상세 (Implementation Details)

### 파싱 과정 (Parsing Process)
1. **Lexical Analysis (Tokenizer)**: 입력된 문자열을 공백과 메타 문자(`|`, `<`, `>`, `<<`, `>>`)를 기준으로 토큰화합니다.
2. **Parsing**: 토큰들을 분석하여 명령어와 인자, 리다이렉션 파일 등을 구조체에 저장합니다.
3. **Variable Expansion**: 환경 변수(`$VAR`)를 실제 값으로 치환합니다.
4. **Quote Removal**: 불필요한 따옴표를 제거합니다.

### 실행 과정 (Execution Process)
1. **파이프 생성**: 파이프가 존재할 경우 `pipe()` 시스템 콜을 사용하여 파이프를 생성합니다.
2. **프로세스 분기**: `fork()`를 호출하여 자식 프로세스를 생성합니다.
3. **리다이렉션 처리**: `dup2()`를 사용하여 표준 입출력을 파일이나 파이프로 연결합니다.
4. **명령어 실행**: `execve()`를 호출하여 명령어를 실행합니다. 빌트인 명령어는 부모 프로세스(일부) 또는 자식 프로세스에서 직접 실행됩니다.

<br />

## 👨‍💻 저자 (Authors)

| 이름 | 역할 | GitHub |
|:---:|:---:|:---:|
| **dukim** | Main Logic, Parsing, Execution | [@dukim](https://github.com/dukim-42) |
| **junkwak** | Signal, Builtins, Utils | [@junkwak](https://github.com/junkwak) |

<br />

---
<p align="center">
  Developed by dukim & junkwak
</p>
