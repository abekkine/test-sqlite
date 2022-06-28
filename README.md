# SQlite3 Multiprocess Access Test

## Usage

```sh
> testQL <fromId> <toId> <valueChange>
```

or

```sh
> testQL <fromId> <toId> <stepId> <valueChange>
```

## Examples

DB list format :
> ... id: value, id: value, id: value ...

Before:
```sh
..., 99: 10, 100: 10, 101: 10, 102: 10, 103: 10, 104: 10, ...
```

```sh
> testQL 100 103 5
```

After:
```sh
..., 99: 10, 100: 15, 101: 15, 102: 15, 103: 15, 104: 10, ...
```

```sh
> testQL 99 103 2 -2
```

After:
```sh
..., 99: 8, 100: 15, 101: 13, 102: 15, 103: 13, 104: 10, ...
```

## Expected Test Result

Before running :
```sh
1: 100, 2: 100, 3: 100, ... , 998: 100, 999: 100, 1000: 100
```

After running following three processes:
```sh
> testQL 1 1000 2
> testQL 1 1000 3
> testQL 1 1000 -4
```

Expected table :
```sh
1: 101, 2: 101, 3: 101, ... , 998: 101, 999: 101, 1000: 101
```
