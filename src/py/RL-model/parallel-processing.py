import multiprocessing

def launch_and_land(rocket_id):
    rocket = Rocket(rocket_id)
    rocket.simulate_landing()

if __name__ == "__main__":
    # Number of parallel rocket simulations
    num_rockets = 5

    # Create a pool of worker processes
    pool = multiprocessing.Pool(processes=num_rockets)

    # Launch multiple rocket simulations in parallel
    rocket_ids = list(range(1, num_rockets + 1))
    pool.map(launch_and_land, rocket_ids)

    # Close the pool and wait for all processes to finish
    pool.close()
    pool.join()
