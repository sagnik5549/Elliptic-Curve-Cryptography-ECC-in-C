import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import make_interp_spline

  
# ECC CURVE PLOT
  

df = pd.read_csv("output/curve_points.csv")

p = 8209

plt.figure(figsize=(10, 10))

plt.scatter(
    df["x"],
    df["y"],
    s=8,
    c="black",
    marker="o",
    label="Curve Points"
)

plt.axhline(
    y=p / 2,
    color="red",
    linestyle="--",
    linewidth=2,
    label="Symmetry Line ($y=p/2$)"
)

plt.title(
    "Elliptic Curve Points over a Finite Field",
    fontsize=16,
    fontweight="bold"
)

plt.xlabel("x", fontsize=13)
plt.ylabel("y", fontsize=13)

plt.gca().set_aspect("equal", adjustable="box")

plt.grid(True, linestyle="--", linewidth=0.5, alpha=0.6)

plt.xlim(df["x"].min() - 1, df["x"].max() + 1)
plt.ylim(df["y"].min() - 1, df["y"].max() + 1)

plt.legend()

plt.tight_layout()

plt.savefig(
    "graphs/ecc_curve_plot.png",
    dpi=300,
    bbox_inches="tight"
)

plt.show()

  
# PLAIN MESSAGE POINTS
  

df = pd.read_csv("output/plain_points.csv")

x = df["X"].to_numpy()
y = df["Y"].to_numpy()

t = np.arange(len(x))
ts = np.linspace(t.min(), t.max(), 300)

xs = make_interp_spline(t, x, k=3)(ts)
ys = make_interp_spline(t, y, k=3)(ts)

plt.figure(figsize=(8, 6))

plt.plot(
    xs,
    ys,
    color="royalblue",
    linewidth=1.5
)

plt.plot(
    x,
    y,
    linestyle="",
    marker="D",
    markersize=7,
    color="red",
    label="Plain Points"
)

plt.title(
    "Plain Points in Elliptic Curve",
    fontsize=16,
    fontweight="bold"
)

plt.xlabel("Pmsg (X)", fontsize=13)
plt.ylabel("Pmsg (Y)", fontsize=13)

plt.grid(True, linestyle="--", linewidth=0.5, alpha=0.6)

plt.legend()

plt.tight_layout()

plt.savefig(
    "graphs/plain_points_plot.png",
    dpi=300,
    bbox_inches="tight"
)

plt.show()

  
# ENCRYPTED (CIPHER) POINTS
  

df = pd.read_csv("output/cipher_points.csv")

x = df["X"].to_numpy()
y = df["Y"].to_numpy()

t = np.arange(len(x))
ts = np.linspace(t.min(), t.max(), 300)

xs = make_interp_spline(t, x, k=3)(ts)
ys = make_interp_spline(t, y, k=3)(ts)

plt.figure(figsize=(8, 6))

plt.plot(
    xs,
    ys,
    color="darkorange",
    linewidth=1.5
)

plt.plot(
    x,
    y,
    linestyle="",
    marker="D",
    markersize=7,
    color="deepskyblue",
    label="Encrypted Points"
)

plt.title(
    "Encrypted Points in Elliptic Curve",
    fontsize=16,
    fontweight="bold"
)

plt.xlabel("Cmsg (X)", fontsize=13)
plt.ylabel("Cmsg (Y)", fontsize=13)

plt.grid(True, linestyle="--", linewidth=0.5, alpha=0.6)

plt.legend()

plt.tight_layout()

plt.savefig(
    "graphs/cipher_points_plot.png",
    dpi=300,
    bbox_inches="tight"
)

plt.show()