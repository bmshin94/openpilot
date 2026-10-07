# openpilot 전수조사 분석 & 활용 가이드 (한국어)

> 📌 **대상 저장소**: https://github.com/bmshin94/openpilot
> 📌 **원본(Upstream)**: https://github.com/commaai/openpilot
> 📌 **작성일**: 2026-10-07
> 📌 **분석 기준 커밋**: `0fe0c22` (Merge pull request #1 from bmshin94/feat/claude-guide)
> 📌 **작성**: 카리나 (Claude Code 개발 파트너) 💖

---

## 📑 목차

1. [한눈에 보는 요약](#1-한눈에-보는-요약)
2. [이게 뭐하는 건지 (전수조사 결과)](#2-이게-뭐하는-건지-전수조사-결과)
3. [폴더별 상세 분석](#3-폴더별-상세-분석)
4. [동작 원리 (파이프라인)](#4-동작-원리-파이프라인)
5. [어떨 때 쓰는 건지](#5-어떨-때-쓰는-건지)
6. [설치 및 사용법](#6-설치-및-사용법)
7. [플러그인 / 스킬 / MCP 여부](#7-플러그인--스킬--mcp-여부)
8. [API 토큰 필요 여부](#8-api-토큰-필요-여부)
9. [AI 에이전트 구축에 도움이 되는가](#9-ai-에이전트-구축에-도움이-되는가)
10. [React / PHP 로 만들 수 있는가](#10-react--php-로-만들-수-있는가)
11. [유튜브 강의 제작 가능성](#11-유튜브-강의-제작-가능성)
12. [수익화 아이디어 10선](#12-수익화-아이디어-10선)
13. [90일 실행 플랜](#13-90일-실행-플랜)
14. [현재 저장소 상태 & 할 일](#14-현재-저장소-상태--할-일)
15. [법적 / 안전 주의사항](#15-법적--안전-주의사항)

---

## 1. 한눈에 보는 요약

| 항목 | 내용 |
|---|---|
| **정체** | openpilot — comma.ai 의 **오픈소스 자율주행(ADAS) 운영체제** |
| **분류** | 독립 실행형 로보틱스 애플리케이션 (플러그인/스킬/MCP 아님) |
| **언어** | Python 3.12 + C/C++ (SCons 빌드) |
| **라이선스** | MIT (상업적 이용 가능) |
| **지원 차량** | 335종 이상 (`docs/CARS.md`) |
| **AI 추론** | 100% 온디바이스 (tinygrad + ONNX), 클라우드 API 호출 없음 |
| **프로세스 수** | 약 30개 데몬 (`openpilot/system/manager/process_config.py`) |
| **IPC** | Cap'n Proto + ZeroMQ 기반 Pub/Sub (`openpilot/cereal`) |
| **서브모듈** | panda, opendbc, msgq, rednose, teleoprtc, tinygrad (6개) |
| **차 없이 개발** | ✅ 가능 (MetaDrive 시뮬레이터 + 로그 replay) |

---

## 2. 이게 뭐하는 건지 (전수조사 결과)

**openpilot 은 "테슬라 오토파일럿 같은 운전자 보조 기능을 내 차에 직접 달 수 있게 해주는 오픈소스 소프트웨어"** 입니다.

### 물리적 구성

```
🚗 자동차 (현대/기아/토요타/혼다 등 335종)
     ↕  차량 전기 신호 (CAN Bus)
🔌 panda  — CAN 통신 어댑터 + 하드웨어 안전 차단기 (C 펌웨어)
     ↕  USB
📱 comma four / comma 3X — 앞유리에 부착하는 전용 리눅스 기기
     └── 이 안에서 openpilot 이 실행됨
```

### 핵심 특징

- **인지 → 판단 → 제어** 자율주행 전체 파이프라인이 실제 동작하는 코드로 공개
- **ISO 26262** 가이드라인 준수, 안전 로직은 별도 C 펌웨어(panda)로 분리
- 주행 데이터를 **녹화(loggerd) → 재생(replay)** 하는 완전한 관측성
- 차 없이도 **시뮬레이터**로 개발/테스트 가능

---

## 3. 폴더별 상세 분석

### 3.1 루트 구조

```
openpilot/
├── openpilot/          # 실제 소스코드 본체
│   ├── selfdrive/      # 주행 로직 (두뇌)
│   ├── system/         # OS 레이어 (카메라/로그/센서/업데이트)
│   ├── common/         # 공용 유틸 (params, api, 필터, 변환)
│   ├── cereal/         # 프로세스 간 통신(IPC) 스키마
│   └── tools/          # 개발 도구 (replay/cabana/sim 등)
├── tools/              # 셋업·릴리즈·차량포팅 스크립트 (op.sh)
├── scripts/            # 린트, CI 헬퍼
├── docs/               # 문서 (CARS.md, SAFETY.md, CONTRIBUTING.md)
├── system/hardware/    # 하드웨어 추상화
├── panda/              # [서브모듈] CAN 하드웨어 펌웨어 + 안전 모델
├── opendbc_repo/       # [서브모듈] 차량 CAN 데이터베이스
├── msgq_repo/          # [서브모듈] 고성능 메시지 큐
├── rednose_repo/       # [서브모듈] 칼만 필터 라이브러리
├── teleoprtc_repo/     # [서브모듈] WebRTC 원격 조작
├── tinygrad_repo/      # [서브모듈] 경량 AI 추론 프레임워크
├── SConstruct          # SCons 빌드 정의
├── Jenkinsfile         # 실제 하드웨어(HIL) 테스트 파이프라인
├── pyproject.toml      # Python 의존성
└── CLAUDE.md           # 👈 사용자가 추가한 카리나 페르소나 설정
```

### 3.2 `openpilot/selfdrive/` — 주행 두뇌

| 경로 | 역할 | 주요 파일 |
|---|---|---|
| `modeld/` | **AI 신경망 추론** — 카메라 → 주행 경로 예측 | `modeld.py`, `dmonitoringmodeld.py`, `parse_model_outputs.py` |
| `controls/` | **제어** — 조향/가감속 명령 생성 | `controlsd.py`, `plannerd.py`, `radard.py` |
| `controls/lib/` | 제어 알고리즘 | `latcontrol_torque.py`, `latcontrol_pid.py`, `longcontrol.py`, `longitudinal_mpc_lib/` |
| `car/` | 차량 추상화 | `card.py`, `cruise.py`, `car_events.py` |
| `locationd/` | **위치·자세 추정 + 자동 캘리브레이션** | `locationd.py`, `calibrationd.py`, `paramsd.py`, `torqued.py`, `lagd.py` |
| `monitoring/` | **운전자 감시(DMS)** — 졸음/부주의 | `dmonitoringd.py`, `policy.py` |
| `selfdrived/` | **상태머신 + 안전 경고** | `selfdrived.py`, `state.py`, `events.py`, `alertmanager.py` |
| `ui/` | 차량 화면 UI (raylib) | `ui.py`, `soundd.py`, `onroad/`, `layouts/`, `widgets/` |
| `pandad/` | CAN 하드웨어 통신 데몬 | `pandad.py` |

### 3.3 `openpilot/system/` — OS 레이어

| 경로 | 역할 |
|---|---|
| `camerad/` | 카메라 캡처 (제로카피 VisionIPC) |
| `loggerd/` | 주행 로그/영상 녹화, 업로드, 삭제 (`uploader.py`, `deleter.py`) |
| `sensord/` | IMU / 자력계 / 온도 센서 |
| `athena/` | 클라우드 원격 통신 (WebSocket, JWT) — `athenad.py`, `registration.py` |
| `manager/` | **프로세스 매니저** — 모든 데몬 생성/감시/재시작 (`process_config.py`) |
| `updated/` | OTA 업데이트 |
| `ubloxd/`, `qcomgpsd/` | GPS 수신 |
| `webrtc/` | 원격 스트리밍 |
| `hardware/` | 하드웨어 추상화 + 온도/전력 관리 (`hardwared.py`) |
| `camerad/webcam/` | PC 웹캠으로 테스트 |

### 3.4 `openpilot/cereal/` — 프로세스 간 통신

- `log.capnp` — **모든 메시지 스키마 정의** (Cap'n Proto)
- `services.py` — 서비스별 주기(Hz), 포트 정의
- `messaging/` — Pub/Sub 구현
- `visionipc.py` — 영상 프레임 제로카피 공유

> 💡 Kafka / Redis Pub-Sub / 이벤트 드리븐 MSA 와 동일한 개념을 **20Hz 실시간**으로 구현한 사례.

### 3.5 `openpilot/tools/` — 개발 도구 (차 없이 개발 가능하게 해주는 핵심)

| 도구 | 설명 | 언어 |
|---|---|---|
| `replay/` | 📼 주행 로그 재생 — 디버깅의 핵심 | C++ |
| `sim/` | 🎮 MetaDrive 시뮬레이터 브릿지 | Python |
| `cabana/` | 🔍 CAN 메시지 뷰어 / 리버스 엔지니어링 | C++ |
| `jotpluggler/` | 📊 로그 데이터 플로팅 (ImGui) | C++ |
| `plotjuggler/` | 📊 PlotJuggler 연동 | Python |
| `camerastream/` | 카메라 네트워크 스트리밍 | Python |
| `joystick/` | 🎮 조이스틱으로 차량 제어 | Python |
| `clip/` | 🎬 주행 영상 클립 추출 | Python |
| `lib/` | 로그 파서, 인증, API 클라이언트 | Python |
| `car_porting/` | 신규 차종 포팅 도구 | Python |
| `longitudinal_maneuvers/`, `lateral_maneuvers/` | 제어 성능 측정용 기동 | Python |

### 3.6 `scripts/` 와 CI

- `scripts/lint/` — `check_dependencies.py`, `check_shell.py`, `check_indentation.py`, `check_added_large_files.py` 등
- `.github/workflows/` — `tests.yaml`, `auto_pr_review.yaml`, `ui_preview.yaml`, `docs.yaml`, `release.yaml`, `diff_report.yaml` 등 9개
- `Jenkinsfile` — comma 내부 **하드웨어 인 더 루프(HIL)** 테스트 (실제 기기 10대로 route 연속 재생)

---

## 4. 동작 원리 (파이프라인)

### 4.1 20Hz 주행 루프

```
① 👁 camerad       카메라로 도로 촬영 (제로카피 VisionIPC)
        ↓
② 🧠 modeld        AI 신경망 추론 → "차선 위치, 주변 차량, 주행 경로" 예측
        ↓          (driving_supercombo.onnx, tinygrad 런타임)
③ 📐 plannerd      목표 속도/곡률 계획 수립 (MPC)
        ↓
④ 🎮 controlsd     실제 조향 토크 / 가감속 계산 (PID, Torque control)
        ↓
⑤ 🔄 card          차종별 CAN 메시지로 변환
        ↓
⑥ 🔌 pandad        panda 하드웨어를 통해 차량에 전송
        ↓
⑦ 🚙 차량 거동     → 다시 ① 로 (약 50ms 주기)

동시 실행:
   😴 dmonitoringd   운전자 얼굴 추적 → 졸음/부주의 경고
   🚨 selfdrived     상태머신 + 이상 감지 시 즉시 해제
   📼 loggerd        전체 입출력 녹화 (AI 학습 + 디버깅)
   📍 locationd      칼만 필터로 위치/자세 추정
   🎯 calibrationd   카메라 장착 각도 자동 보정
```

### 4.2 안전 계층 (가장 배울 만한 설계)

```
AI 모델 출력  →  controlsd 한계 검사  →  panda 펌웨어(C) 최종 검증  →  차량
                                          ↑
                           소프트웨어가 오작동해도 여기서 물리적으로 차단
                           (토크/가속 한도, 상태 검증, ISO 26262)
```

---

## 5. 어떨 때 쓰는 건지

| 사용 시나리오 | 필요한 것 |
|---|---|
| 🚗 실제 차량에 자율주행 적용 | comma four + 차종별 하네스 + 지원 차량 |
| 🎮 PC 시뮬레이션 연구/개발 | PC만 (Ubuntu 24.04 권장) |
| 📼 주행 로그 분석/디버깅 | PC + (내 로그 사용 시) comma 계정 |
| 🔧 신규 차종 포팅 | 차량 + panda + cabana (바운티 대상 💰) |
| 📚 자율주행 학습 교재 | PC만 |
| 🏗 실시간 시스템 아키텍처 학습 | PC만 |

---

## 6. 설치 및 사용법

### 6.1 PC 개발 환경 (권장 시작점)

**요구사항**: Ubuntu 24.04 (주 타깃) / macOS (대부분 동작) / Windows → **WSL2** 필수
**Python**: 3.12.3 이상 ~ 3.13 미만 (`.python-version`)

```bash
# 1) 클론 (서브모듈 포함)
git clone --recurse-submodules https://github.com/bmshin94/openpilot.git
cd openpilot

# 1-1) 이미 클론한 경우 (현재 저장소 상태)
git submodule update --init --recursive
git lfs pull                       # AI 모델 실제 파일 다운로드

# 2) 의존성 설치
tools/op.sh setup

# 3) 파이썬 가상환경 활성화
source .venv/bin/activate

# 4) 빌드
scons -u -j$(nproc)
```

### 6.2 `op` 명령어 전체 (tools/op.sh 실측)

| 분류 | 명령 | 설명 |
|---|---|---|
| **시스템** | `op setup` | op 툴 + 의존성 설치 |
| | `op check` | 개발환경 점검 (git, OS) |
| | `op venv` | 가상환경 셸 진입 |
| | `op build [-j4]` | 빌드 실행 |
| | `op switch [REMOTE] <BRANCH>` | 브랜치 전환 (⚠️ 변경사항 삭제) |
| | `op start` / `op stop` | openpilot 시작/중지 |
| | `op auth` | comma 계정 인증 |
| | `op esim` | 기기 eSIM 프로필 관리 |
| **도구** | `op replay [--demo]` | 주행 로그 재생 |
| | `op cabana` | CAN 메시지 뷰어 |
| | `op juggle [--demo]` | PlotJuggler 실행 |
| | `op clip` | 주행 클립 생성 (Linux) |
| | `op docs` | 문서 빌드/서브 |
| | `op adb` / `op ssh` | 기기 접속 |
| **테스트** | `op sim` | 시뮬레이터 실행 |
| | `op test` | 전체 유닛 테스트 |
| | `op lint` | 린터 실행 |
| | `op post-commit` | 린터를 post-commit 훅으로 설치 |
| **옵션** | `-d, --dir` / `--dry` / `-n, --no-verify` | 디렉터리 지정 / 드라이런 / 검증 생략 |

### 6.3 시뮬레이터 실행

```bash
./openpilot/tools/sim/launch_openpilot.sh    # 터미널 1
./openpilot/tools/sim/run_bridge.py          # 터미널 2
#   옵션: --joystick  --high_quality  --dual_camera
```

| 키 | 기능 |
|---|---|
| `1` | 크루즈 Resume / 속도 증가 |
| `2` | 크루즈 Set / 속도 감소 (처음 2 → engage) |
| `3` | 크루즈 취소 |
| `s` | 해제 (브레이크 시뮬레이션) |
| `r` | 시뮬레이션 리셋 |
| `i` | 시동(Ignition) 토글 |
| `q` | 전체 종료 |

### 6.4 CTF 챌린지 (툴 학습용 추천)

`tools/CTF.md` — comma 공식 해킹 챌린지

```bash
cd openpilot/tools/replay
./replay '0c7f0c7f0c7f0c7f|2021-10-13--13-00-00' --dcam --ecam
# 다른 터미널
openpilot/selfdrive/ui/ui
```
각 세그먼트에 flag 2개씩 숨겨져 있음.

### 6.5 실차 설치 (브랜치 선택)

| comma four | comma 3X | 설치 URL | 설명 |
|---|---|---|---|
| `release-mici` | `release-tizi` | `openpilot.comma.ai` | 안정 릴리즈 |
| `release-mici-staging` | `release-tizi-staging` | `openpilot-test.comma.ai` | 릴리즈 스테이징 |
| `nightly` | `nightly` | `openpilot-nightly.comma.ai` | 개발 최신 (불안정) |
| `nightly-dev` | `nightly-dev` | `installer.comma.ai/commaai/nightly-dev` | 실험 기능 포함 |

chestnut 기기: `release-chestnut`, `release-chestnut-staging`, `nightly-chestnut`, `nightly-chestnut-dev`

---

## 7. 플러그인 / 스킬 / MCP 여부

### 결론: **세 가지 모두 아님** ❌

전수조사 확인 결과:

| 확인 항목 | 결과 |
|---|---|
| `.claude/` 디렉터리 | ❌ 없음 |
| `.claude/skills/` (Agent Skill) | ❌ 없음 |
| `.claude-plugin/plugin.json` (플러그인) | ❌ 없음 |
| `.mcp.json` / MCP 서버 구현 | ❌ 없음 |
| Claude 관련 파일 | ✅ `CLAUDE.md` 1개 (사용자가 직접 추가한 페르소나 설정, 커밋 `83eb67d`) |

### 정확한 분류

> **openpilot = 독립 실행형(standalone) 로보틱스 애플리케이션**
> Python + C++ 로 작성된 약 30개 리눅스 데몬의 묶음. SCons 로 빌드하여 전용 하드웨어에서 실행.

| 구분 | 정의 | openpilot |
|---|---|---|
| 🔌 플러그인 | Claude Code 기능 확장 패키지 | ❌ |
| 📚 스킬 | Claude 에게 작업 지침을 주는 폴더 | ❌ |
| 🔗 MCP | AI ↔ 외부 도구 연결 표준 프로토콜 서버 | ❌ |
| 🚗 독립 앱 | 자체 실행되는 완성 소프트웨어 | ✅ |

### 확장 아이디어 (직접 만들 수 있는 것)

```
.claude/skills/openpilot-dev/SKILL.md
  → openpilot 코드 수정 시 린트/테스트 규칙, CAN 작업 가이드 등

openpilot-mcp (MCP 서버)
  → .rlog 주행 로그를 파싱해 AI 에게 제공
  → "어제 주행에서 개입이 몇 번 있었나?" 를 LLM 이 답변
```

---

## 8. API 토큰 필요 여부

### 8.1 기능별 정리

| 작업 | 토큰 필요 | 비고 |
|---|:---:|---|
| 코드 읽기 / 분석 | ❌ | |
| 빌드 (`scons -u`) | ❌ | |
| 시뮬레이터 (`op sim`) | ❌ | MetaDrive 로컬 실행 |
| 유닛 테스트 (`op test`) | ❌ | |
| 데모 로그 replay (`--demo`) | ❌ | 공개 route |
| **내 주행 로그** replay / 플로팅 | ✅ | comma 계정 JWT |
| comma connect 연동 | ✅ | |
| 실제 기기 등록 | ✅ (자동) | 기기가 자체 처리 |

### 8.2 토큰 발급 (`openpilot/tools/lib/auth.py`)

```bash
op auth              # Google 계정 (브라우저 OAuth)
op auth github       # GitHub 계정
op auth apple        # Apple 계정
op auth jwt ey...    # JWT 직접 입력 (CI/CD 용)
```

- 저장 위치: `~/.comma/auth.json` → `{"access_token": "..."}`
- CI 용 JWT 발급: https://jwt.comma.ai
- 관련 코드: `openpilot/tools/lib/auth_config.py` (`get_token` / `set_token` / `clear_token`)

### 8.3 기기 자체 인증 (`openpilot/common/api.py`)

comma 기기는 토큰을 받지 않고 **하드웨어에 심긴 키페어로 JWT 를 자가 서명**합니다.

```python
API_HOST = os.getenv('API_HOST', 'https://api.commadotai.com')
KEYS = {"id_rsa": "RS256", "id_ecdsa": "ES256"}   # /persist/comma/ 에 저장
# 유효기간 1시간 JWT 를 기기가 직접 발급
token = jwt.encode(payload, self.private_key, algorithm=self.jwt_algorithm)
```

- 기기 식별자: `dongle_id` (`openpilot/system/athena/registration.py`)
- 2024년 3월 이후 생산 기기는 `/persist/` 에 정보가 사전 저장됨

> 💡 **IoT 디바이스 인증 설계의 모범 사례** — 키페어 기반 self-signed JWT 패턴.

### 8.4 중요한 오해 정정

**LLM API 키(`ANTHROPIC_API_KEY` 등)는 전혀 필요 없습니다.**
openpilot 의 AI 는 **100% 온디바이스 추론**입니다.

- 모델: `driving_supercombo.onnx`, `dmonitoring_model.onnx`, `big_driving_tinygrad.pkl`
- 런타임: **tinygrad** (`tinygrad_repo` 서브모듈)
- 네트워크가 끊겨도 주행 기능은 정상 동작 (실시간 제어는 네트워크 지연을 허용할 수 없음)

---

## 9. AI 에이전트 구축에 도움이 되는가

### 결론: **코드 재사용은 ❌ / 아키텍처 교재로는 최상급 ⭐⭐⭐⭐⭐**

### 9.1 직접 사용 불가 이유

| LLM 에이전트 필수 요소 | openpilot |
|---|---|
| LLM 호출 / 프롬프트 | ❌ |
| Tool calling | ❌ |
| RAG / 벡터 DB | ❌ |
| 에이전트 루프 / MCP | ❌ |
| 자연어 처리 | ❌ |

openpilot 의 AI 는 **비전 기반 회귀 모델**(사진 → 경로 좌표)이며 LLM 이 아닙니다.

### 9.2 구조적 동형성 (Sense → Think → Act)

| openpilot | AI 에이전트 |
|---|---|
| ① `camerad` 센서 입력 | ① 사용자 입력 / 환경 관찰 |
| ② `modeld` 모델 추론 | ② LLM 추론 |
| ③ `plannerd` 계획 수립 | ③ Planning / Chain-of-Thought |
| ④ `controlsd` 행동 실행 | ④ Tool calling / Action |
| ⑤ `selfdrived` 안전 검증 | ⑤ Guardrail / Validation |
| ⑥ `loggerd` 전체 기록 | ⑥ Observability / Tracing |
| ♻️ 20Hz 루프 | ♻️ Agent loop |

### 9.3 에이전트 설계에 그대로 적용 가능한 5가지 교훈

1. **독립 안전 계층 (Guardrail)** — 모델 출력을 모델과 분리된 검증기가 반드시 통과시킨다.
   참고: `selfdrive/selfdrived/state.py`, `events.py`, `panda` 안전 모델
2. **선언적 상태머신** — 에이전트 상태 전이를 명시적으로 정의 (`state.py`)
3. **Pub/Sub 메시지 계약** — 멀티 에이전트 통신 설계 (`cereal/log.capnp`)
4. **완전 관측성 + 재생(Replay)** — 모든 입출력 기록 후 그대로 재현해 디버깅
   (`loggerd` + `tools/replay`) → LangSmith/Langfuse 가 하는 일의 원형
5. **프로세스 매니저와 자동 복구** — 워커 장애 시 재시작 (`system/manager/`)

### 9.4 요약

| 목적 | 가능성 |
|---|---|
| openpilot 코드를 에이전트에 재사용 | ❌ |
| openpilot 설계를 보고 에이전트 아키텍처 학습 | ✅ 최상 |
| MCP 를 만들어 openpilot 을 에이전트로 제어/분석 | ✅ 가능, 틈새 선점 가능 |
| 주행 로그를 LLM 이 분석하게 하기 | ✅ 수익화 가능 |

---

## 10. React / PHP 로 만들 수 있는가

### 결론: **openpilot 본체는 ❌ / 주변 서비스는 ✅ 전면 가능**

### 10.1 본체 포팅 불가 이유

| 요구사항 | React/PHP |
|---|---|
| 20Hz 실시간 루프 (50ms 데드라인) | ❌ GC 정지, 이벤트루프 지터 |
| 실시간 프로세스 우선순위 (`config_realtime_process`) | ❌ 리눅스 RT 스케줄링 필요 |
| USB / CAN 하드웨어 직접 제어 | ❌ |
| 온디바이스 NPU/GPU 추론 (tinygrad) | ❌ |
| 제로카피 공유메모리 영상 전달 (VisionIPC) | ❌ |
| ISO 26262 안전 등급 | ❌ |

### 10.2 React / PHP 로 만들 수 있는 것

| 제품 | 스택 | 설명 |
|---|---|---|
| 📊 주행 로그 대시보드 | React + Recharts | 거리/시간/자율주행 비율/개입 횟수 시각화 |
| 🗺 주행 경로 지도 | React + Mapbox | GPS 로그 궤적 + 히트맵 |
| 🎬 웹 기반 replay 플레이어 | React + HLS.js | 영상 + 데이터 오버레이 동기 재생 |
| 🚨 개입(disengage) 분석 리포트 | React + Laravel | "언제, 왜 해제됐는지" 분석 |
| 🚐 플릿 관리 백오피스 | Laravel + React | 다중 차량 모니터링 (B2B 유료) |
| 🔍 차종 호환성 검색 | Next.js | `docs/CARS.md` 파싱 → 검색/필터 |
| 🛒 부품 견적 계산기 | React | 차종 선택 → 필요 부품 + 가격 |
| 📱 원격 모니터링 앱 | React Native | `athenad` WebSocket 연동 |
| 🤖 AI 주행 코칭 | Next.js + Claude API | 로그 요약 → 운전 습관 코멘트 |

### 10.3 현실적 아키텍처

```
🚗 comma 기기 (openpilot: C++/Python)
      │  athenad WebSocket / comma API (JWT)
      ↓
🐍 Python 수집·파싱 서버
      │  ← openpilot/tools/lib 재사용 (Cap'n Proto 파서 필요)
      │  → JSON 으로 정규화
      ↓
🐘 PHP(Laravel) API — 인증 / DB / 과금
      ↓
⚛️ React 프론트엔드 — 대시보드 / 차트 / 플레이어
```

> 핵심: **로그 파싱만 Python 에 위임**하고, 그 이후는 React/PHP 가 주력이 되는 구조가 가장 현실적.

---

## 11. 유튜브 강의 제작 가능성

### 결론: **가능하며, 국내 경쟁이 적은 고가치 소재** ✅

### 11.1 적합한 이유

| 이유 | 설명 |
|---|---|
| MIT 라이선스 | 코드 공개/수정/상업적 콘텐츠 제작 합법 |
| 강한 비주얼 | 시뮬레이터, 차선 인식 시각화 → 썸네일/영상 임팩트 |
| 국내 경쟁 희박 | 한국어 openpilot 심화 콘텐츠 거의 없음 |
| 명확한 타깃 | 자율주행 취준생, 로보틱스 입문자, 자동차 애호가 |
| 낮은 진입장벽 | 차량 없이 시뮬레이터만으로 촬영 가능 |
| 무한한 분량 | 약 30개 데몬, 6개 서브모듈, 7개 도구 → 장기 시리즈 가능 |

### 11.2 추천 커리큘럼

**시즌 1 — 입문**
1. 테슬라 오토파일럿을 오픈소스로? openpilot 전격 해부
2. 내 PC 에 자율주행 깔기 — 설치 완전정복 (`op setup`)
3. 차 없이 자율주행 체험 — 시뮬레이터 실습 (`op sim`) ⭐ 킬러 영상
4. 내 차도 될까? 335종 지원 차량 확인법

**시즌 2 — 아키텍처**
5. openpilot 은 1초에 20번 무슨 일을 하나 (파이프라인)
6. 30개 프로세스가 대화하는 방법 — cereal & Cap'n Proto
7. AI 가 운전하는 원리 — modeld & tinygrad
8. 핸들은 이렇게 돌아간다 — PID 와 MPC
9. AI 가 오작동해도 안전한 이유 — panda 안전 모델 ⭐
10. 졸음운전 감지 원리 — DMS 분석

**시즌 3 — 실습/도구**
11. 블랙박스 되감기 — replay 로 주행 디버깅
12. CAN 통신 리버스 엔지니어링 입문 — cabana
13. 로그 데이터 분석 — jotpluggler
14. comma CTF 챌린지 함께 풀기

**시즌 4 — 응용/수익**
15. 새 차종 포팅해서 바운티 받는 방법
16. 주행 데이터 대시보드 만들기 (React 실습)
17. openpilot 에서 배우는 AI 에이전트 설계
18. 자율주행 회사 취업 포트폴리오 만들기

### 11.3 제작 팁

| 항목 | 팁 |
|---|---|
| 화면 녹화 | OBS Studio + 시뮬레이터 + 터미널 분할 |
| 영상 소재 | `openpilot/tools/clip/run.py` 로 주행 클립 추출 |
| 썸네일 | 차선 인식 오버레이 화면 활용 |
| 자막 | 영어 자막 추가 → 글로벌 조회수 확대 |
| 길이 | 입문 8~12분 / 심화 15~25분 |

### 11.4 준수 사항

- 설명란에 `openpilot by comma.ai (MIT License)` + 저장소 링크 표기
- "ALPHA QUALITY SOFTWARE FOR RESEARCH PURPOSES ONLY" 고지 언급
- 국내 실도로 적용은 자동차관리법 / 보험 확인 필요 명시
- comma 공식 영상 무단 재업로드 금지 → 직접 녹화
- 위험 운전(핸들 미파지 등) 조장 금지

---

## 12. 수익화 아이디어 10선

### Tier S — 즉시 시작 가능

#### ① comma 공식 바운티
| 항목 | 내용 |
|---|---|
| 수익 | 건당 $300 ~ $10,000+ |
| 난이도 | ⭐⭐⭐⭐ |
| 초기비용 | 시뮬레이터만: 0원 / 차종 포팅: 기기+하네스 |
| 리스크 | 🟢 없음 |

https://comma.ai/bounties → PR 제출 → 머지 시 지급. 문서/테스트/버그 수정 등 소액부터 시작 권장.
부가 이득: **openpilot 컨트리뷰터 이력** 확보.

#### ② 유튜브 + 온라인 강의 (최우선 추천)
| 항목 | 내용 |
|---|---|
| 수익 | 광고 + 멤버십 + 유료 강의(건당 수백만원 가능) |
| 난이도 | ⭐⭐ |
| 초기비용 | 거의 0원 |
| 리스크 | 🟢 MIT 라이선스로 합법 |

```
1단계: 유튜브 무료 영상 → 구독자 + 광고 수익
2단계: 인프런/유데미 유료 강의 (₩8~15만)
3단계: 1:1 멘토링 / 기업 교육 / 컨퍼런스 강연
```

#### ③ 주행 데이터 분석 SaaS
| 항목 | 내용 |
|---|---|
| 수익 | 월 구독 $5~20 / 사용자 |
| 난이도 | ⭐⭐⭐ |
| 초기비용 | 서버 비용 |
| 리스크 | 🟡 개인정보(주행데이터) 동의/보관 정책 필요 |

제품 컨셉: "내 openpilot 주행 성적표"
- 주간/월간 리포트 (거리, 시간, 자율주행 비율)
- 개입(disengage) 분석 TOP 5
- 주행 경로 히트맵
- 급제동/급가속 기반 운전 습관 점수
- LLM 기반 주간 코칭 코멘트
- 커뮤니티 리더보드

스택: Python(파싱) → Laravel API → React 대시보드. 타깃: 전 세계 openpilot 사용자.

---

### Tier A — 중간 난이도, 높은 수익성

#### ④ B2B 플릿(차량 관제) 솔루션
| 항목 | 내용 |
|---|---|
| 수익 | 월 수백만~수천만원 (B2B) |
| 난이도 | ⭐⭐⭐⭐⭐ |
| 초기비용 | 높음 |
| 리스크 | 🔴 안전/법규 |

타깃: 운수·물류·렌터카·대리운전 업체.
**전략: "자율주행"을 팔지 말고 `selfdrive/monitoring/` 기반 "운전자 안전 모니터링"만 판매** → 법적 리스크 대폭 감소, 수요는 더 큼.
- 졸음/휴대폰 사용 실시간 감지 + 관리자 알림
- 사고 전후 영상 자동 보존
- 운전자별 안전 점수 / 급제동·과속 리포트

#### ⑤ 설치 대행 + 차종 포팅 전문 서비스
| 항목 | 내용 |
|---|---|
| 수익 | 설치 건당 20~50만원 / 포팅 의뢰 100만원+ |
| 난이도 | ⭐⭐⭐⭐ |
| 초기비용 | 중간 |
| 리스크 | 🔴 국내 법규 확인 필수 |

기기 구매 대행 → 하네스 매칭 → 설치 → 캘리브레이션 → 사용 교육.
⚠️ 자동차관리법 / 튜닝 승인 / 보험 면책 이슈 → **사업화 전 법률 상담 필수**.

#### ⑥ 니치 웹서비스 (광고/제휴)
| 항목 | 내용 |
|---|---|
| 수익 | 애드센스 + 제휴 수익 |
| 난이도 | ⭐⭐ |
| 초기비용 | 거의 0원 |
| 리스크 | 🟢 없음 |

- 내 차 openpilot 호환 검색기 (`docs/CARS.md` 파싱)
- 부품 견적 자동 계산기
- 한국어 openpilot 위키
- 주간 업데이트 뉴스레터 (`RELEASES.md` 자동 요약)
- 브라우저 차선인식 데모

---

### Tier B — 장기 / 간접 수익

#### ⑦ openpilot MCP 서버 & 에이전트 툴킷
주행 로그를 AI 가 읽을 수 있게 하는 MCP 서버를 오픈소스로 공개 → 인지도 → 컨설팅/강연.
현재 사실상 공백 영역으로 **선점 가능**.

#### ⑧ 커리어 전환 (금액 기준 최대 가치)
| 경로 | 설명 |
|---|---|
| 취업 | 현대차/모비스/42dot/자율주행 스타트업 — 컨트리뷰터 이력이 강력한 스펙 |
| 프리랜스 | Upwork 등 "openpilot/ADAS 개발" 시급 $50~150 |
| 컨설팅/강연 | 기업 교육, 컨퍼런스 |
| comma 직접 지원 | 원격 채용 진행 중 |

#### ⑨ 하드웨어/액세서리 커머스
3D 프린팅 마운트, 커스텀 하네스, 거치대 등. 난이도는 낮으나 마진·재고 리스크 있음.

#### ⑩ 한국형 포크 배포 + 후원
해외 선례: sunnypilot, dragonpilot, FrogPilot → Patreon/후원 모델.
한국형 아이디어: 하이패스 감속, 과속카메라 연동, 한글 UI/음성.
⚠️ 안전 책임 문제가 크므로 신중 접근 필요.

---

### 종합 비교표

| # | 아이디어 | 수익성 | 난이도 | 비용 | 리스크 | 추천 순위 |
|---|---|:---:|:---:|:---:|:---:|:---:|
| ② | 유튜브/강의 | 💰💰💰 | ⭐⭐ | 0원 | 🟢 | **1위** |
| ③ | 데이터 SaaS | 💰💰💰 | ⭐⭐⭐ | 낮음 | 🟡 | **2위** |
| ⑥ | 니치 웹서비스 | 💰 | ⭐⭐ | 0원 | 🟢 | **3위** |
| ① | 바운티 | 💰💰 | ⭐⭐⭐⭐ | 낮음 | 🟢 | 4위 |
| ⑦ | MCP 툴킷 | 💰 | ⭐⭐⭐ | 0원 | 🟢 | 5위 |
| ⑧ | 커리어 | 💰💰💰💰 | ⭐⭐⭐ | 0원 | 🟢 | 장기 최고 |
| ④ | B2B 플릿 | 💰💰💰💰 | ⭐⭐⭐⭐⭐ | 높음 | 🔴 | 장기 |
| ⑤ | 설치대행 | 💰💰 | ⭐⭐⭐⭐ | 중간 | 🔴 | 법률검토 후 |
| ⑩ | 포크 후원 | 💰 | ⭐⭐⭐⭐⭐ | 낮음 | 🔴 | 신중 |
| ⑨ | 커머스 | 💰 | ⭐⭐ | 중간 | 🟡 | 보조수익 |

---

## 13. 90일 실행 플랜

```
📅 1~30일차 — 콘텐츠 + 학습 병행
   □ 환경 세팅 (submodule init, git lfs pull, op setup, scons -u)
   □ 시뮬레이터 실행 및 녹화
   □ 유튜브 입문 3편 업로드 (개요 / 설치 / 시뮬레이터)
   □ CTF 풀면서 replay·cabana 익히기

📅 31~60일차 — 웹서비스 MVP
   □ "호환 차량 검색기" Next.js 제작 및 배포
   □ 애드센스 + comma 제휴 링크 연결
   □ .rlog 로그 파서 Python 프로토타입 (tools/lib 활용)
   □ 유튜브 아키텍처 편 4~6편

📅 61~90일차 — 수익화 본격화
   □ 데이터 대시보드 SaaS 베타 오픈 (React + Laravel)
   □ 인프런 강의 촬영 시작
   □ 소액 바운티 PR 1건 제출 → 컨트리뷰터 이력 확보
   □ openpilot-mcp 오픈소스 공개
```

**핵심 전략**: ②유튜브로 **학습과 콘텐츠를 동시에** 생산하고, 모인 관심을 ③SaaS 로 전환 → 학습·콘텐츠·제품의 선순환 구조.

---

## 14. 현재 저장소 상태 & 할 일

### 14.1 확인된 상태 (2026-10-07, 커밋 `0fe0c22`)

| 항목 | 상태 |
|---|---|
| 서브모듈 6개 (`panda`, `opendbc_repo`, `msgq_repo`, `rednose_repo`, `teleoprtc_repo`, `tinygrad_repo`) | ⚠️ **모두 비어 있음** (미초기화) |
| AI 모델 파일 (`driving_supercombo.onnx` 등) | ⚠️ **Git LFS 포인터만 존재** (121~134 바이트) |
| Python 가상환경 `.venv` | ⚠️ 없음 |
| 빌드 산출물 | ⚠️ 없음 |
| `CLAUDE.md` | ✅ 카리나 페르소나 설정 적용됨 |

### 14.2 실행하려면 필요한 작업

```bash
# 1) 서브모듈 초기화
git submodule update --init --recursive

# 2) LFS 실제 파일 다운로드 (AI 모델)
git lfs install
git lfs pull

# 3) 의존성 설치 + 가상환경
tools/op.sh setup
source .venv/bin/activate

# 4) 빌드
scons -u -j$(nproc)

# 5) 동작 확인
op test            # 유닛 테스트
op replay --demo   # 데모 로그 재생
op sim             # 시뮬레이터
```

---

## 15. 법적 / 안전 주의사항

### 저장소 자체 경고 (README)

> **THIS IS ALPHA QUALITY SOFTWARE FOR RESEARCH PURPOSES ONLY. THIS IS NOT A PRODUCT.
> YOU ARE RESPONSIBLE FOR COMPLYING WITH LOCAL LAWS AND REGULATIONS.
> NO WARRANTY EXPRESSED OR IMPLIED.**

### 반드시 확인할 사항

| 항목 | 내용 |
|---|---|
| ⚖️ **국내 법규** | 한국에서 ADAS 개조는 자동차관리법상 튜닝 승인 대상 여부 확인 필요 |
| 🛡 **보험** | 사고 시 보험 면책 가능성 → 보험사 사전 확인 |
| 👤 **운전 책임** | 운전 책임은 **100% 운전자**. 상시 주의·조향 개입 가능 상태 유지 |
| 🔒 **개인정보** | 주행 로그는 위치·영상 포함 → 수집·보관·제3자 제공 시 동의 및 암호화 필요 |
| 📜 **라이선스** | MIT — 재배포 시 저작권·라이선스 고지문 유지 |
| ☁️ **데이터 업로드** | 기본적으로 주행 데이터가 comma 서버에 업로드됨 (설정에서 비활성화 가능). 운전자 카메라/마이크는 옵트인 시에만 기록 |

### 사업화 전 체크리스트

- [ ] 변호사 / 교통 관련 행정기관 상담 (실차 관련 사업 시)
- [ ] 개인정보 처리방침 작성 (데이터 서비스 시)
- [ ] 면책 조항 및 이용약관 작성
- [ ] 안전 고지문 상시 노출
- [ ] MIT 라이선스 고지 포함

---

## 📎 참고 링크

| 구분 | 링크 |
|---|---|
| 🔗 **이 저장소** | https://github.com/bmshin94/openpilot |
| 🔗 원본(Upstream) | https://github.com/commaai/openpilot |
| 📚 공식 문서 | https://docs.comma.ai |
| 🗺 로드맵 | https://docs.comma.ai/contributing/roadmap/ |
| 🤝 컨트리뷰팅 | https://github.com/commaai/openpilot/blob/master/docs/CONTRIBUTING.md |
| 💬 커뮤니티 Discord | https://discord.comma.ai |
| 🛒 하드웨어 구매 | https://comma.ai/shop |
| 💰 바운티 | https://comma.ai/bounties |
| 💼 채용 | https://comma.ai/jobs#open-positions |
| ☁️ comma connect | https://connect.comma.ai/ |
| 🔑 CI용 JWT 발급 | https://jwt.comma.ai |
| 📖 커뮤니티 위키 | https://github.com/commaai/openpilot/wiki |
| 🔌 panda (안전 펌웨어) | https://github.com/commaai/panda |
| 🚙 opendbc (CAN DB) | https://github.com/commaai/opendbc |
| 🧠 tinygrad | https://github.com/tinygrad/tinygrad |
| 🎮 MetaDrive 시뮬레이터 | https://github.com/metadriverse/metadrive |

### 저장소 내부 주요 문서

| 문서 | 설명 |
|---|---|
| `README.md` | 프로젝트 개요, 브랜치, 설치 |
| `docs/CARS.md` | 지원 차량 335종 전체 목록 |
| `docs/SAFETY.md` | 안전 모델 설명 |
| `docs/LIMITATIONS.md` | 기능 한계 |
| `docs/CONTRIBUTING.md` | 기여 가이드 |
| `docs/INTEGRATION.md` | 차량 통합 |
| `docs/DEBUGGING_SAFETY.md` | 안전 디버깅 |
| `docs/concepts/logs.md` | 로그 구조 |
| `docs/how-to/car-port.md` | 신규 차종 포팅 방법 |
| `docs/how-to/replay-a-drive.md` | 주행 재생 방법 |
| `docs/how-to/turn-the-speed-blue.md` | 첫 코드 수정 튜토리얼 |
| `tools/README.md` | 개발 환경 셋업 |
| `tools/CTF.md` | CTF 챌린지 |
| `RELEASES.md` | 전체 릴리즈 노트 |

---

*이 문서는 저장소 전수조사(폴더 구조, 소스코드, 설정 파일, CI 워크플로 직접 확인)를 기반으로 작성되었습니다.* 💖
