# Struct and Enum Examples

## Overview
Two comprehensive examples demonstrating the use of `struct` and `enum` keywords in the Algo compiler.

## Files

### 1. `50_struct_enum_combined.algo` - Complex Example
**Lines**: 226  
**Instructions**: 2201  
**Description**: Comprehensive example showing multiple enums and simulated structs

**Features demonstrated**:
- Multiple enum definitions (Color, Status, Gender, CarType)
- Enum values with auto-increment and explicit values
- Simulated struct fields (car_color, car_status, car_speed)
- Multiple struct instances (car1, car2, car3, person)
- Enum constants in conditionals
- Switch statements with enum values (using numeric literals)
- Array simulation with struct-like patterns
- Finding maximum values across multiple "struct instances"
- Enum immutability demonstration

**Enums defined**:
- `Color`: RED(0), GREEN(1), BLUE(2), YELLOW(3), BLACK(4)
- `Status`: INACTIVE(0), ACTIVE(1), PENDING(2), ERROR(99)
- `Gender`: MALE(1), FEMALE(2), OTHER(3)
- `CarType`: SEDAN(100), SUV(200), TRUCK(300), SPORTS(400)

### 2. `51_struct_enum_simple.algo` - Clean Example
**Lines**: 175  
**Instructions**: 2103  
**Description**: Cleaner, more focused example ideal for learning

**Features demonstrated**:
- Basic enum definitions with auto-increment
- Enum with explicit values
- Simulated struct with multiple fields
- Multiple struct instances (car1, car2)
- Comparing struct field values
- Using enum constants in conditionals
- Modifying struct fields
- Displaying all enum values
- Clear documentation and comments

**Enums defined**:
- `Color`: RED(0), GREEN(1), BLUE(2), BLACK(3), WHITE(4)
- `Status`: OFF(0), ON(1), MAINTENANCE(2)

**Simulated structs**:
```c
// Conceptual struct (simulated):
struct Car {
    int color;   // car_color variable
    int status;  // car_status variable
    int speed;   // car_speed variable
};
```

## Key Concepts

### Enum Implementation
- **True compile-time constants**: Enum values don't consume registers
- **Immutable**: Cannot assign to enum constants (e.g., `RED = 5` causes error)
- **Auto-increment**: Values increment from 0 unless specified
- **Explicit values**: Can set specific values (e.g., `ERROR = 99`)
- **Mixed mode**: Can combine auto-increment and explicit values

### Struct Simulation
Since the A1M architecture is register-based without memory:
- **No real struct types**: Cannot allocate memory for struct instances
- **Field simulation**: Each field becomes a separate variable
- **Naming convention**: `structname_fieldname` (e.g., `car1_color`)
- **No dot operator**: Use underscore instead of dot
- **Multiple instances**: Create separate variable sets for each instance

### Limitations
1. **Switch case labels**: Must use integer literals, not enum constants
   - ✗ `case RED:` (not supported)
   - ✓ `case 0:  // RED` (works)

2. **No struct member access**: Cannot use dot operator
   - ✗ `car.color = RED` (not supported)
   - ✓ `car_color = RED` (works)

3. **No struct definition**: Cannot declare struct types
   - Struct keyword recognized but not implemented
   - Use separate variables instead

## Usage Examples

### Enum Usage
```c
// Define enum
enum Color {
    RED,     // 0
    GREEN,   // 1
    BLUE     // 2
}

// Use enum values
let my_color = RED;              // Assign constant
if (my_color == BLUE) { ... }    // Compare with constant
print(GREEN);                     // Print value (1)

// Invalid operations (will cause compile error):
// RED = 5;           // Cannot assign to constant
// RED++;             // Cannot increment constant
```

### Struct Simulation
```c
// Conceptual struct (for documentation only)
// struct Point { int x; int y; };

// Actual implementation
let point1_x = 10;
let point1_y = 20;

let point2_x = 30;
let point2_y = 40;

// Use the "fields"
let distance_x = point2_x - point1_x;
let distance_y = point2_y - point1_y;
```

### Combined Usage
```c
enum Status { OFF = 0, ON = 1 }

// Simulated: struct Device { int status; int power; };
let device1_status = OFF;
let device1_power = 0;

// Turn on device
device1_status = ON;
device1_power = 100;

// Check status
if (device1_status == ON) {
    print("Device is ON with power: ");
    print(device1_power);
}
```

## Testing

Both examples are included in the automated test suite:

```bash
./test_c_keywords.sh
```

Expected output:
```
Testing 50_struct_enum_combined...
  ✓ PASSED
Testing 51_struct_enum_simple...
  ✓ PASSED
```

## See Also
- `46_enum.algo` - Comprehensive enum-only tests
- `47_struct.algo` - Struct simulation examples
- `C_KEYWORDS_IMPLEMENTATION.md` - Full implementation details
