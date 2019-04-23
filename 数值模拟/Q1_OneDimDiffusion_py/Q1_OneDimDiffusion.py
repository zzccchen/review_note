import plotly


def thermal_conductivity(T_old):
    T_new[0] = 100
    for i in range(1, N_max-1):
        T_new[i] = T_old[i] + alpha * \
            (T_old[i + 1] - 2 * T_old[i] + T_old[i - 1])
    T_new[N_max - 1] = T_new[N_max - 2]
    # print(T_old)
    # print(T_new)
    # print("//")
    return T_new


if __name__ == "__main__":
    N_max = 60  # total amount of nodes
    T_new = [36.8] * 60  # record new temperature at t+1
    T_old = [36.8] * 60  # record old temperature at t

    delta_x = 0.5
    delta_t = 0.1
    alpha = 0.001
    alpha /= (delta_x * delta_x / delta_t)

    maxLoops = 300000

    print("maxLoops ", maxLoops)
    print("Well done! Initialized successfully.")
    print("Now, the main loops are starting... ")

    for loops in range(maxLoops+1):
        T_old = thermal_conductivity(T_old)

    plotly.offline.plot([{'x': [i for i in range(100)], 'y': T_new}],
                        image_height=600,
                        image_width=1600)
