import subprocess

def run_test(cpp_path, tb_path, prj_name="test_prj"):
    # Pure English path
    cmd = [r"D:\Xilinx\Vitis_HLS\2024.2\bin\vitis_hls.bat", "run_hls.tcl", prj_name, cpp_path, tb_path]
    print(f"\nExecuting: {' '.join(cmd)}")
    
    # Force GBK decoding
    result = subprocess.run(cmd, capture_output=True, text=True, encoding='gbk', errors='replace')
    
    # Print logs (Pure English tags)
    print("=== LOG_START ===")
    print(result.stdout)
    print(result.stderr)
    print("=== LOG_END ===")
    
    # Check results
    if "CSIM_FAIL" in result.stdout or "ERROR" in result.stdout or "Error" in result.stdout:
        print("RESULT: FAIL")
        return False
    elif "CSIM_PASS" in result.stdout:
        print("RESULT: PASS")
        return True
    else:
        print("RESULT: UNKNOWN")
        return False

if __name__ == "__main__":
    print("--- Test 1: Correct ---")
    run_test("C:/Users/34226/Desktop/hls_project/src/fir.cpp", "C:/Users/34226/Desktop/hls_project/src/fir_tb.cpp", "prj_correct")
    
    print("\n--- Test 2: Syntax Error ---")
    run_test("C:/Users/34226/Desktop/hls_project/src/fir_error_syntax.cpp", "C:/Users/34226/Desktop/hls_project/src/fir_tb.cpp", "prj_err_syntax")
    
    print("\n--- Test 3: Logic Error ---")
    run_test("C:/Users/34226/Desktop/hls_project/src/fir_error_logic.cpp", "C:/Users/34226/Desktop/hls_project/src/fir_tb.cpp", "prj_err_logic")