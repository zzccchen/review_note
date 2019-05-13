import plotly


def thermal_conductivity(T_old):
    T_new[0] = 100
    for i in range(1, N_max-1):
        T_new[i] = T_old[i] + alpha * \
            (T_old[i + 1] - 2 * T_old[i] + T_old[i - 1])
    T_new[-1] = T_old[-2] + alpha * (T_old[-2] - T_old[-1]) \
        + 0.0100 * delta_x * (25 - T_old[-1])
    # print(T_old)
    # print(T_new)
    # print("//")
    return T_new


if __name__ == "__main__":
    N_max = 60  # total amount of nodes
    T_new = [100] * 60  # record new temperature at t+1
    T_old = [100] * 60  # record old temperature at t
    T_old[-30:] = [25]*30

    delta_x = 0.5
    delta_t = 0.1
    alpha = 0.001
    alpha /= (delta_x * delta_x / delta_t)

    maxLoops = 300000
    maxFrame = 100
    loops = 0
    frame = 0

    print("maxLoops ", maxLoops)
    print("maxFrame ", maxFrame)
    print("Well done! Initialized successfully.")
    print("Now, the main loops are starting... ")

    for loops in range(maxLoops+1):
        T_old = thermal_conductivity(T_old)

    plotly.offline.plot([{'x': [i for i in range(100)], 'y': T_new}],
                        image_height=600,
                        image_width=1600)
