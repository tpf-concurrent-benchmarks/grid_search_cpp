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

| Measurement         | 4 Nodes             | 8 Nodes              | 16 Nodes            |
|---------------------|---------------------|----------------------|---------------------|
| Worker Throughput   | 3.5 Results/Second  | 3.45 Results/Second  | 3.42 Results/Second |
| Combined Throughput | 14.0 Results/Second | 28.00 Results/Second | 55.5 Results/Second |
| Work-time Variation | 0.1%                | 0.16%                | 0.12%               |
| Memory Usage        | 5.6-8.9 MB/Worker   | 7-9 MB/Worker        | 7.0-8.4 MB/Worker   |
| CPU Usage           | 99.9%/Worker        | 99.9%/Worker         | 99.9%/Worker        |
| Completion Time     | 28.7 Minutes        | 14.5 Minutes         | 7.3 Minutes         |
