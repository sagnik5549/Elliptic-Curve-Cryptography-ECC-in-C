import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV exported by the C program
df = pd.read_csv("curve_points.csv")

# Prime modulus (set according to your curve)
p = 8209

# Create figure
plt.figure(figsize=(10, 10))

# Plot curve points
plt.scatter(
    df["x"],
    df["y"],
    s=8,                 # Marker size
    c="black",           # Point color
    marker="o",
    label="Curve Points"
)

# Draw symmetry line (y = p/2)
plt.axhline(
    y=p / 2,
    color="red",
    linestyle="--",
    linewidth=2,
    label="Symmetry Line ($y = p/2$)"
)

# Title and labels
plt.title(
    "Elliptic Curve Points over a Finite Field",
    fontsize=16,
    fontweight="bold"
)

plt.xlabel("x", fontsize=13)
plt.ylabel("y", fontsize=13)

# Equal scaling on both axes
plt.gca().set_aspect("equal", adjustable="box")

# Grid
plt.grid(
    True,
    linestyle="--",
    linewidth=0.5,
    alpha=0.6
)

# Axis limits
plt.xlim(df["x"].min() - 1, df["x"].max() + 1)
plt.ylim(df["y"].min() - 1, df["y"].max() + 1)

# Show integer ticks only for small curves
if df["x"].max() <= 100:
    plt.xticks(range(int(df["x"].min()), int(df["x"].max()) + 1))
    plt.yticks(range(int(df["y"].min()), int(df["y"].max()) + 1))

# Legend
plt.legend()

# Improve layout
plt.tight_layout()

# Save figure
plt.savefig(
    "ecc_curve_plot.png",
    dpi=300,
    bbox_inches="tight"
)

# Display
plt.show()