// parameter_property_decorators.ts

function logParameter(target: any, propertyKey: string, parameterIndex: number) {
    const existingLoggedParameters: number[] = Reflect.getOwnMetadata("log_parameters", target, propertyKey) || [];
    existingLoggedParameters.push(parameterIndex);
    Reflect.defineMetadata("log_parameters", existingLoggedParameters, target, propertyKey);
}

function logAccessor(target: any, propertyKey: string, descriptor: PropertyDescriptor) {
    const original = descriptor.get;
    descriptor.get = function () {
        console.log(`Accessing ${propertyKey}`);
        return original && original.apply(this);
    };
}

class Example {
    private _value: number = 0;

    @logAccessor
    get value() {
        return this._value;
    }

    set value(val: number) {
        this._value = val;
    }

    method(@logParameter msg: string) {
        console.log(msg);
    }
}

const ex = new Example();
ex.value = 42;
console.log(ex.value);
ex.method("Hello");
