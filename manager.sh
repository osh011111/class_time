#!/bin/bash

# 컴파일 수행 (scheduler.c가 변경되었을 수 있으므로 항상 최신 유지)
if [ -f "scheduler.c" ]; then
    gcc -o scheduler scheduler.c
else
    echo "Error: scheduler.c 파일이 없습니다."
    exit 1
fi

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

            echo "⏳ 시간표를 계산 중입니다..."
            
            # C 프로그램 실행 파트부분
            ./scheduler $input_times
            ;;
        
        2)
            echo "기능 구현 예정입니다."
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