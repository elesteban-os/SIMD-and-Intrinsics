import subprocess
import pandas as pd
import plotly.graph_objs as go

# 1. compile the C++ code
compile_cmd = [
    "g++", "-std=c++17", "-O2",
    "main.cpp",
    "random_str/random-str.cpp",
    "serial/char_count_serial.cpp",
    "simd/char_count_simd.cpp",
    "-o", "test", "-mavx"
]
compilation = subprocess.run(compile_cmd, capture_output=True, text=True)
if compilation.returncode != 0:
    print("Error de compilación:\n", compilation.stderr)
    exit(1)

# 2. excute the compiled program
run = subprocess.run(["./test"], capture_output=True, text=True)
print(run.stdout)
if run.returncode != 0:
    print("Error al ejecutar el programa:\n", run.stderr)
    exit(1)

# 3. read the results from the CSV file
df = pd.read_csv("results.csv")

# order by Length
df = df.sort_values("Length")

# 4. graphic 1: Length vs CountSerial y CountSIMD
fig1 = go.Figure()
fig1.add_trace(go.Scatter(x=df["Length"], y=df["CountSerial"], mode='lines+markers', name="CountSerial"))
fig1.add_trace(go.Scatter(x=df["Length"], y=df["CountSIMD"], mode='lines+markers', name="CountSIMD"))
fig1.update_layout(
    title="Length vs CountSerial y CountSIMD",
    xaxis_title="Length",
    yaxis_title="Count",
    legend_title="Método"
)
fig1.write_html("length_vs_count.html")
fig1.show()

# 5. graphic 2: Length vs TimeSerial_ns y TimeSIMD_ns
fig2 = go.Figure()
fig2.add_trace(go.Scatter(x=df["Length"], y=df["TimeSerial_ns"], mode='lines+markers', name="TimeSerial_ns"))
fig2.add_trace(go.Scatter(x=df["Length"], y=df["TimeSIMD_ns"], mode='lines+markers', name="TimeSIMD_ns"))
fig2.update_layout(
    title="Length vs TimeSerial_ns y TimeSIMD_ns",
    xaxis_title="Length",
    yaxis_title="Time (ns)",
    legend_title="Método"
)
fig2.write_html("length_vs_time.html")
fig2.show()