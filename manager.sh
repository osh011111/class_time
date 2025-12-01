#!/bin/bash

# 컴파일 수행 (scheduler.c가 변경되었을 수 있으므로 항상 최신 유지)
if [ -f "scheduler.c" ]; then
    gcc -o scheduler scheduler.c
else
    echo "Error: scheduler.c 파일이 없습니다."
    exit 1
fi

LOG_FILE="schedule.log"

while true; do
    echo ""
    echo "----------------------------------------"
    echo "   강의실 시간 배정 관리 시스템"
    echo "----------------------------------------"
    echo "1. 시간 배정 요청 (Input)"
    echo "2. 과거 로그 검색 (Log Search)"
    echo "3. 종료 (Exit)"
    echo -n "메뉴를 선택하세요: "
    read choice

    case $choice in
        1)
            echo -n "시간을 입력하세요 (예: 09-14 12-13 13-14): "
            read input_times

            # 유효성 검사 (형식 체크)
            if [[ ! "$input_times" =~ ^([0-9]{2}-[0-9]{2}[[:space:]]*)+$ ]]; then
                echo -e "\033[31m❌ [Error] 입력 형식이 잘못되었습니다. (형식: 09-11 10-12)\033[0m"
                continue
            fi

            echo "⏳ 시간표를 계산 중입니다..."
            
            # C 프로그램 실행
            result=$(./scheduler $input_times)
            current_date=$(date "+%Y-%m-%d %H:%M:%S")

            # 결과 화면 출력
            echo ""
            echo "$result"
            echo ""

            # 로그 파일 저장
            {
                echo "========================================"
                echo "작업 일시: $current_date"
                echo "입력 데이터: $input_times"
                echo "$result"
                echo "========================================"
            } >> $LOG_FILE
            
            echo "✅ 결과가 $LOG_FILE 에 저장되었습니다."
            ;;
        
        2)
            if [ ! -f "$LOG_FILE" ]; then
                echo "📭 저장된 로그 파일이 없습니다."
                continue
            fi

            echo -n "검색할 날짜를 입력하세요 (YYYY-MM-DD): "
            read target_date

            # 날짜 형식 유효성 검사 (정규표현식)
            # ^:시작, [0-9]{4}:숫자4개, $:끝
            if [[ ! "$target_date" =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}$ ]]; then
                echo "❌ 날짜 형식이 올바르지 않습니다. (예: 2025-11-30)"
                continue
            fi

            echo ""
            echo "📄 [$target_date] 로그 검색 결과:"
            echo "----------------------------------------"

            # [핵심 로직] awk를 사용한 블록 단위 검색
            # RS(Record Separator): 데이터를 나누는 기준을 줄바꿈(\n)이 아닌 '====' 선으로 설정
            # $0 ~ target : 그 덩어리 안에 우리가 찾는 날짜가 들어있으면 출력
            awk -v target="$target_date" '
                BEGIN { RS = "========================================" } 
                $0 ~ target { print "========================================" $0 }
            ' "$LOG_FILE"

            echo "----------------------------------------"
            echo "검색이 완료되었습니다."
            ;;
            
        3)
            echo "프로그램을 종료합니다."
            break
            ;;
            
        *)
            echo "잘못된 입력입니다. 다시 선택해주세요."
            ;;
    esac
done