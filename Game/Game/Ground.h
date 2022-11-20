#pragma once

#include "Object.h"

class Ground :
    public Object
{
public:
    Ground();
    ~Ground() final = default;

    void Update() final;
    void Render() final;
    void OnTriggerEnter(Object* other) final;
    void OnTriggerStay(Object* other) final;
    void OnTriggerExit(Object* other) final;
};
