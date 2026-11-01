import subprocess
import json
import os
import glob

# --- PATH SETTINGS ---
WORKSPACE = r"C:\Users\34226\Desktop\hls_project"
JSON_DIR = os.path.join(WORKSPACE, "json_inputs")
SRC_DIR = os.path.join(WORKSPACE, "src")
RESULTS_DIR = os.path.join(WORKSPACE, "results")
SCRIPTS_DIR = os.path.join(WORKSPACE, "scripts")
VITIS_BAT = r"D:\Xilinx\Vitis_HLS\2024.2\bin\vitis_hls.bat"

# Create dirs if not exist
os.makedirs(RESULTS_DIR, exist_ok=True)
os.makedirs(os.path.join(WORKSPACE, "reports"), exist_ok=True)

def run_test(json_file):
    base_name = os.path.splitext(os.path.basename(json_file))[0]
    print(f"\nProcessing {base_name}...")
    
    with open(json_file, 'r', encoding='utf-8') as f:
        data = json.load(f)
    
    kernel_code = data.get("kernel", "")
    tb_code = data.get("testbench", "")
    
    # Auto-detect top function name
    top_func = "unknown"
    for line in kernel_code.split('\n'):
        if 'void ' in line and '(' in line and ';' not in line:
            top_func = line.split('void ')[1].split('(')[0].strip()
            break
            
    print(f"Detected top function: {top_func}")
    
    cpp_path = os.path.join(SRC_DIR, f"{base_name}_kernel.cpp").replace("\\", "/")
    tb_path = os.path.join(SRC_DIR, f"{base_name}_tb.cpp").replace("\\", "/")
    
    with open(cpp_path, 'w', encoding='utf-8') as f: f.write(kernel_code)
    with open(tb_path, 'w', encoding='utf-8') as f: f.write(tb_code)
    
    # Run Vitis
    cmd = [VITIS_BAT, "run_hls.tcl", f"prj_{base_name}", cpp_path, tb_path, top_func]
    result = subprocess.run(cmd, capture_output=True, text=True, encoding='gbk', errors='replace', cwd=SCRIPTS_DIR)
    output = result.stdout + result.stderr
    
    # Save log
    log_path = os.path.join(RESULTS_DIR, f"{base_name}.log")
    with open(log_path, 'w', encoding='utf-8') as f: f.write(output)
    
    # Determine Pass/Fail
    status = "FAIL"
    if "CSIM_PASS" in output and "CSYNTH_PASS" in output:
        status = "PASS"
    elif "CSIM_PASS" in output and "CSYNTH_FAIL" in output:
        status = "PASS_CSIM_BUT_CSYNTH_FAIL"
        
    print(f"Result for {base_name}: {status}")
    return base_name, top_func, status

if __name__ == "__main__":
    json_files = glob.glob(os.path.join(JSON_DIR, "*.json"))
    
    # Sort to run in order 1, 2, 3, 4, 5
    json_files.sort()
    
    results = []
    
    for jf in json_files:
        res = run_test(jf)
        results.append(res)
        
    # Generate CSV table
    csv_path = os.path.join(RESULTS_DIR, "summary.csv")
    with open(csv_path, 'w', encoding='utf-8') as f:
        f.write("Testcase,TopFunction,Status\n")
        for r in results:
            f.write(f"{r[0]},{r[1]},{r[2]}\n")
            
    print("\nAll tests finished. Check results/summary.csv")
