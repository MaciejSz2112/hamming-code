import os
import subprocess
import pytest

BUILD_DIR = "build"
MATRIX_GEN_EXE = os.path.join(BUILD_DIR, "matrix_generator.exe")
CODER_EXE = os.path.join(BUILD_DIR, "coder_module.exe")

@pytest.fixture(scope="session", autouse=True)
def compile_project():
  print("\n[Pytest] Setting up environment and compiling binaries...")

  os.makedirs(BUILD_DIR, exist_ok=True)

  config_res = subprocess.run(
    ["cmake", "-B", BUILD_DIR, "-S", ".", "-G", "minGW Makefiles"],
    capture_output=True,
    text=True
  )

  build_gen_res = subprocess.run(
    ["cmake", "--build", BUILD_DIR, "--target", "matrix_generator"],
    capture_output=True,
    text=True
  )

  try:
    gen_process = subprocess.run(
      [MATRIX_GEN_EXE],
      input="15\n",
      capture_output=True,
      text=True,
      timeout=5
    )

    if gen_process.returncode != 0:
      pytest.fail(
        f"Matrix generator execution failed with code {gen_process.returncode}.\n"
        f"STDOUT: {gen_process.stdout}\n"
        f"STDERR: {gen_process.stderr}"
      )

  except subprocess.TimeoutExpired:
    pytest.fail("Matrix generator timed out waiting for input")

  build_coder_res = subprocess.run(
    ["cmake", "--build", BUILD_DIR, "--target", "coder_module"],
    capture_output=True,
    text=True
  )

  if build_coder_res.returncode != 0:
    pytest.fail(f"Building coder_module failed:\n{build_coder_res.stderr}")
  
  print("[Pytest] Compulation successful. Running tests...\n")


def test_hamming_end_to_end():
  
  test_message = "01001011000"
  input_file_path = "files/input.txt"
  output_file_path = "files/output.txt"

  os.makedirs('files', exist_ok=True)

  with open(input_file_path, "w", encoding="utf-8") as f:
    f.write(test_message)
  
  if os.path.exists(output_file_path):
    os.remove(output_file_path)

  process = subprocess.run(
    [CODER_EXE],
    capture_output=True,
    text=True
  )

  assert process.returncode == 0, f"CoderModule failed with error: {process.stderr}"
  assert os.path.exists(output_file_path), f"The encoder did not generate '{output_file_path}' file"

  with open(output_file_path, "r", encoding="utf-8") as f:
    decoded_message = f.read()
  
  decoded_message = decoded_message.strip('\x00').strip()
  assert decoded_message == test_message, f"Regression detected!\nExpected: '{test_message}'\nGot: '{decoded_message}'"