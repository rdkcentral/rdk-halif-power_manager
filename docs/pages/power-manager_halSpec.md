# Power Manager HAL Documentation

## History

| Date(DD/MM/YY) | Comment | Version |
| ---- | ------- | ------- |
| 21/09/23 | Second Release  | 1.0.1 |
| 05/06/23  | First Release | 1.0.0 |

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Description](#description)
- [Component Runtime Execution Requirements](#component-runtime-execution-requirements)
  - [Initialization and Startup](#initialization-and-startup)
  - [Threading Model](#threading-model)
  - [Process Model](#process-model)
  - [Memory Model](#memory-model)
  - [Power Management Requirements](#power-management-requirements)
  - [Asynchronous Notification Model](#asynchronous-notification-model)
  - [Blocking calls](#blocking-calls)
  - [Internal Error Handling](#internal-error-handling)
  - [Persistence Model](#persistence-model)
- [Non-functional requirements](#non-functional-requirements)
  - [Logging and debugging requirements](#logging-and-debugging-requirements)
  - [Memory and performance requirements](#memory-and-performance-requirements)
  - [Quality Control](#quality-control)
  - [Licensing](#licensing)
  - [Build Requirements](#build-requirements)
  - [Variability Management](#variability-management)
  - [Platform or Product Customization](#platform-or-product-customization)
- [Interface API Documentation](#interface-api-documentation)
  - [Theory of operation and key concepts](#theory-of-operation-and-key-concepts)
  - [Sequence Diagram](#sequence-diagram)
  - [State Diagram](#state-diagram)

## Acronyms, Terms and Abbreviations

- `HAL`:    Hardware Abstraction Layer
- `CPE`:    Customer Premises Equipment
- `CPU`:    Central Processing Unit
- `IR`:     Infra-red
- `HDMI`:   High-Definition Multimedia Interface
- `A/V`:    Audio/Video
- `HDD`:    Hard Drive Disk

## References

## Description


The diagram below describes a high-level software architecture of the module stack.

```mermaid
%%{ init : { "theme" : "forest", "flowchart" : { "curve" : "linear" }}}%%
flowchart TD
y[Caller]<-->x[Power Manager HAL];
x[Power Manager HAL]<-->z[SOC Drivers];
style y fill:#99CCFF,stroke:#333,stroke-width:0.3px,align:left
style z fill:#fcc,stroke:#333,stroke-width:0.3px,align:left
style x fill:#9f9,stroke:#333,stroke-width:0.3px,align:left
 ```

This interface provides a set of `APIs` to facilitate communication through the `caller` and `HAL`.

The Power manger `HAL` provides a set of `APIs` to initialize, query and set the power state, and query and set the wake up source.

## Component Runtime Execution Requirements

### Initialization and Startup

`Caller` must initialize by calling `PLAT_INIT()` before calling any other `API`.

### Threading Model

This interface is not required to be thread safe. Any `caller` invoking the `APIs` must ensure calls are made in a thread safe manner.

### Process Model

This interface is required to support a single instantiation with a single process.

### Memory Model

The `caller` is responsible to pass message buffer and free it for transmit request.

### Power Management Requirements

The Power Manager `HAL` is involved to set the power management states ON, OFF, STANDBY, and LIGHT_SLEEP. 

### Asynchronous Notification Model

This interface is not required to support asynchronous notification.

### Blocking calls

There are no blocking calls. Synchronous calls must complete within a reasonable time period. Any call that can fail due to the lack of response from the connected device must have a timeout period and the function must return the relevant error code.

### Internal Error Handling

All the `APIs` must return error synchronously as a return argument. `HAL` is responsible for handling system errors (e.g. out of memory) internally.

### Persistence Model

There is no requirement for the interface to persist any setting information. `Caller` is responsible to persist any settings related to the `HAL`.

## Non functional requirements


### Logging and debugging requirements

This interface is required to support DEBUG, INFO and ERROR messages. INFO and DEBUG must be disabled by default and enabled when required.

### Memory and performance requirements

This interface is required to not cause excessive memory and CPU utilization.

### Quality Control

- This interface is required to perform static analysis, our preferred tool is Coverity.
- Have a zero-warning policy with regards to compiling. All warnings are required to be treated as errors.
- Copyright validation is required to be performed, e.g.: Black duck, FossID.
- Use of memory analysis tools like Valgrind are encouraged to identify leaks/corruptions.
- `HAL` Tests will endeavour to create worst case scenarios to assist investigations.
- Improvements by any party to the testing suite are required to be fed back.

### Licensing

The `HAL` implementation is expected to released under the Apache License 2.0.

### Build Requirements

The source code must build into a shared library and must be named as `libiarmmgrs-power-hal.so`. The build mechanism must be independent of Yocto.

### Variability Management

Any changes in the `APIs` must be reviewed and approved by the component architects.

### Platform or Product Customization

This interface is not required to have any platform or product customizations.

## Interface API Documentation

`API` documentation will be provided by Doxygen which will be generated from the header file.

### Theory of operation and key concepts

The `caller` is expected to have complete control over the life cycle of the `HAL`.

- Initialize the `HAL` using function: `PLAT_INIT()` before making any other `API` calls.  If `PLAT_INIT()` call fails, the `HAL` must return the respective error code, so that the `caller` can retry the operation.

- Power status settings can be controlled using the functions `PLAT_API_SetPowerState()` and `PLAT_API_SetWakeupSrc()` and existing status can be queried using the functions `PLAT_API_GetPowerState()` and `PLAT_API_GetWakeupSrc()`.

- De-initialize the `HAL` using the function: `PLAT_TERM()`.


### **Sequence Diagram**
<br/>


```mermaid
%%{ init : { "theme" : "default", "flowchart" : { "curve" : "stepBefore" }}}%%
   sequenceDiagram
    participant Caller as Caller
    participant HAL as Power Manager HAL
    participant Device as HAL Device Control/Driver
    Caller->>HAL:PLAT_INIT()
    HAL-->>Caller:return
    Caller->>HAL:PLAT_API_SetPowerState()
    Note over HAL: Sets the current power state.
    HAL->>Device:Setting power mode.
    Device-->>HAL:Return
    HAL-->>Caller:return
    Caller->>HAL:PLAT_API_GetPowerState()
    Note over HAL: Gets the current power state.
    HAL->>Device:Getting current Power Mode
    Device-->>HAL:Return
    HAL-->>Caller:return
    Caller->>HAL:PLAT_API_SetWakeupSrc()
    Note over HAL: Sets the wake-up source.
    HAL-->>Caller:return
    Caller->>HAL:PLAT_API_GetWakeupSrc()
    Note over HAL: Gets the current wake-up source.
    HAL-->>Caller:return
    Caller ->>HAL:PLAT_TERM()
    HAL-->>Caller:return
 ```

### **State Diagram**
<br/>

![State Diagram](/docs/pages/images/pwrmgr_state_diagram.png)
    
    

<br/>
