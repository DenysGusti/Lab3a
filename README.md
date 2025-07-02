# Claim

In this lab, I have implemented the following tasks:

## T1: (10%) Output a valid black image file (you will get many of them when continuing and this will be the only time you need them).

## T2: (25%) Output an image with spheres on it after ray tracing them.

## T3: (25%) Be able to read in geometry from the specified xml files. (example1.xml)

## T4: (30%) Implement basic Phong illumination and shading. (example2.xml)

## T5: (10%) Render example3.xml with shadows.

---

## Tested Environments

### Development Computer:

- **OS:** Windows 24H2

### Testing Computer:

- ALMIGHTY
- **OS:**  Linux almighty 5.15.0-131-generic #141-Ubuntu SMP Fri Jan 10 21:18:28 UTC 2025 x86_64 x86_64 x86_64 GNU/Linux

---

## Additional And General Remarks:

---

## Resources:

- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

---

## How to Run

1. **Change into the project base directory.**

Before running any commands, make sure you are in the project root (where `project.sh` is located).

2. **Make the build script executable.**

```bash
chmod +x project.sh
```

3. **Configure the project.**

```bash
./project.sh configure --release
```

4. **Build the project.**

```bash
./project.sh build --release
```

5. **Run the executable.**

```bash
./project.sh run --release <path-to-scene.xml>
```

Make sure the scene XML file path is correct relative to the current working directory.

### Examples:

```bash
./project.sh run --release ../scenes/example1.xml
```

```bash
./project.sh run --release ../scenes/example2.xml
```

```bash
./project.sh run --release ../scenes/example3.xml
```

6. **Clean build files if needed.**

```bash
./project.sh clean
```

---