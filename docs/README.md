# Benchmarks

## Measurements

### Server

| Measurement         | 4 Nodes             | 8 Nodes             | 16 Nodes            |
|---------------------|---------------------|---------------------|---------------------|
| Worker Throughput   | 2.42 Results/Second | 2.28 Results/Second | 2.26 Results/Second |
| Combined Throughput | 9.60 Results/Second | 18.2 Results/Second | 34.8 Results/Second |
| Work-time Variation | 0.83%               | 0.25%               | 0.38%               |
| Memory Usage        | 1.7-9.0 MB/Worker   | 1.6-9.0 MB/Worker   | 1.3-8.6 MB/Worker   |
| CPU Usage           | 100%/Worker         | 100%/Worker         | 100%/Worker         |
| Completion Time     | 41.5 Minutes        | 22.0 Minutes        | 11.2 Minutes        |

Average measurements using the [specified configuration](measurements/README.md)

## Subjective analysis

### Ease of development

C++ being a low level language leaves a lot of the decision to the developer. This is great as you can optimize and write blazing fast code but comes with the downside of hard to write code that demands a lot more careful consideration from the programmer.
The different memory management options take a lot of learning to understand and use properly and a lot of the knowledge can't be transferred easily from other programming languages. 
The compiler is very smart and will often warn or generate faster code, but you still need the knowledge for the rest of the cases where the compiler can't make the best decision on its own. 
In addition, the error message are cryptic and hard to understand and debugging the code is a challenge. Overall a really powerful language in the right hands but with an incredibly steep learning curve.

### External Resources

C++ counts with a lot of tools by virtue of being one of the most popular languages.
With this said, with no standardized package management solution, installing and using those libraries can be a challenge. 
CMake tries to solve this problem, but it is still far from making the C++ environment easy to use.