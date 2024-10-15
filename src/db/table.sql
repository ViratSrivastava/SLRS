
CREATE DATABASE rocket_data;

\c rocket_data;

CREATE TABLE descent_data (
    id SERIAL PRIMARY KEY,
    time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    altitude DOUBLE PRECISION,
    engine_count INT,
    stage_separated BOOLEAN
);
