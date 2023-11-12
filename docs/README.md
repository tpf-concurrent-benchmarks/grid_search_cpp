# Benchmarks

## Measurements

| Measurement         | 4 Nodes              | 8 Nodes              | 16 Nodes            |
|---------------------|----------------------|----------------------|---------------------|
| Worker Throughput   | 3.37 Results/Second  | 3.45 Results/Second  | 3.42 Results/Second |
| Combined Throughput | 13.53 Results/Second | 28.00 Results/Second | 55.5 Results/Second |
| Work-time Variation | 4.5%                 | 0.16%                | 0.12%               |
| Memory Usage        | 3.5-4.5 MB/Worker    | 7-9 MB/Worker        | 7.0-8.4 MB/Worker   |
| CPU Usage           | 99.9%/Worker         | 99.9%/Worker         | 99.9%/Worker        |
| Completion Time     | 31.6 Minutes         | 14.5 Minutes         | 7.3 Minutes         |

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