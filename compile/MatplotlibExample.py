# Python 3. Install once: python3 -m pip install matplotlib
# Run: python3 MatplotlibExample.py
import matplotlib.pyplot as plt

x = [1, 2, 3, 4, 5]
y = [n * n for n in x]
fig, ax = plt.subplots(figsize=(5.6, 2.6), layout="constrained")
ax.plot(x, x, "o-", label="n")   # Points connected by a solid line.
ax.plot(x, y, "s--", label="n^2")  # Square markers, dashed line.
ax.set(title="Linear and quadratic growth", xlabel="n", ylabel="f(n)")
ax.set_xticks(x)
ax.grid(True, alpha=0.3)
ax.legend()
# Save before show(); output is in the current working directory.
fig.savefig("matplotlib_example.png", dpi=180)
plt.show()  # Open the graph window; close it to finish the script.
# On a server without a display, omit show() and keep savefig().
