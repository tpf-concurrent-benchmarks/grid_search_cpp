## Measurements

The system was run on the designated server, using the [Griewank function](https://www.sfu.ca/~ssurjano/griewank.html), with 4,8 and 16 nodes; with the following parameters:

```json
{
  "data": [
    [-600, 600, 0.2, 5],
    [-600, 600, 0.2, 5],
    [-600, 600, 0.2, 5]
  ],
  "agg": "MIN",
  "maxItemsPerBatch": 10800000
}
```

### Average Summary

#### FaMAF Server

| Measurement         | 4 Nodes             | 8 Nodes             | 16 Nodes            |
|---------------------|---------------------|---------------------|---------------------|
| Worker Throughput   | 2.42 Results/Second | 2.28 Results/Second | 2.26 Results/Second |
| Combined Throughput | 9.60 Results/Second | 18.2 Results/Second | 34.8 Results/Second |
| Work-time Variation | 0.83%               | 0.25%               | 0.38%               |
| Memory Usage        | 1.7-9.0 MB/Worker   | 1.6-9.0 MB/Worker   | 1.3-8.6 MB/Worker   |
| Network Usage (Tx)  | 740 B/(s * Worker)  | 710 B/(s * Worker)  | 680 B/(s * Worker)  |
| Network Usage (Rx)  | 160 B/(s * Worker)  | 155 B/(s * Worker)  | 150 B/(s * Worker)  |
| CPU Usage           | 100%/Worker         | 100%/Worker         | 100%/Worker         |
| Completion Time     | 41.5 Minutes        | 22.0 Minutes        | 11.2 Minutes        |

#### Cloud (GCP)

| Measurement         | 4 Nodes             | 8 Nodes             | 16 Nodes            |
|---------------------|---------------------|---------------------|---------------------|
| Worker Throughput   | 1.87 Results/Second | 1.65 Results/Second | 1.68 Results/Second |
| Combined Throughput | 7.48 Results/Second | 13.2 Results/Second | 26.8 Results/Second |
| Work-time Variation | 0.432%              | 0.705%              | 3.80%               | 
| Memory Usage        | 1.29-4.00 MB/Worker | 1.35-2.95 MB/Worker | 1.00-4.50 MB/Worker |
| Network Usage (Tx)  | 580 B/(s * Worker)  | 550 B/(s * Worker)  | 600 B/(s * Worker)  |
| Network Usage (Rx)  | 130 B/(s * Worker)  | 130 B/(s * Worker)  | 132 B/(s * Worker)  |
| CPU Usage           | 100%/Worker         | 100%/Worker         | 100%/Worker         |
| Completion Time     | 54.0 Minutes        | 26.7 Minutes        | 15.1 Minutes        |


