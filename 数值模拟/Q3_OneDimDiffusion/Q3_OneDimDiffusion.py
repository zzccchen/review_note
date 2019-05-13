import plotly
import plotly.graph_objs as go


def thermal_conductivity(T_old):
    T_new[0] = 900
    for i in range(1, 48):
        T_new[i] = T_old[i] + alpha1 * \
            (T_old[i + 1] - 2 * T_old[i] + T_old[i - 1])

    T_new[48] = T_old[48] + alpha1 * (T_old[47] - T_old[48]) \
        + 0.0500 * delta_x * (T_old[49] - T_old[48])
    
    T_new[49] = T_old[49] + 0.0500 * delta_x * \
        (T_old[50] - 2 * T_old[49] + T_old[48])

    T_new[50] = T_old[50] + 0.0500 * delta_x * (T_old[49] - T_old[50]) \
        + alpha2 * (T_old[51] - T_old[50])

    for i in range(51, 129):
        T_new[i] = T_old[i] + alpha2 * \
            (T_old[i + 1] - 2 * T_old[i] + T_old[i - 1])

    T_new[-1] = T_old[-1] + alpha2 * (T_old[-2] - T_old[-1]) \
        + 0.0050 * delta_x * (25 - T_old[-1])
    # print(T_old)
    # print(T_new)
    # print("//")
    return T_new


if __name__ == "__main__":
    T_new = [500] * 130  # record new temperature at t+1
    T_old = [500] * 130  # record old temperature at t

    delta_x = 1
    delta_t = 0.1
    alpha1 = 0.002
    alpha1 /= (delta_x * delta_x / delta_t)
    alpha2 = 0.001
    alpha2 /= (delta_x * delta_x / delta_t)

    maxLoops = 3000

    print("maxLoops ", maxLoops)
    print("Well done! Initialized successfully.")
    print("Now, the main loops are starting... ")

    for loops in range(maxLoops+1):
        T_old = thermal_conductivity(T_old)

    trace = go.Scatter(
        x=[i for i in range(130)],
        y=T_new,
        mode='lines',
        name='Temperature Line'
    )
    data = go.Data([trace])

    plotly.offline.plot(data,
                        image_height=600,
                        image_width=1600)
