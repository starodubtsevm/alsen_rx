#ifndef DIGITALFILTERABSTRACT_H
#define DIGITALFILTERABSTRACT_H

class IDigitalFilter
{
public:
    IDigitalFilter()
    {
       FPrefilter = nullptr;
       FPostfilter = nullptr;
    }
    virtual ~IDigitalFilter() {}

    virtual double filter(const double ASample) = 0;
    virtual void setPrefilter(IDigitalFilter * APreFilter) { FPrefilter = APreFilter; }
    virtual void setPostfilter(IDigitalFilter * APostFilter) { FPostfilter = APostFilter; }
protected:
    IDigitalFilter * FPrefilter;
    IDigitalFilter * FPostfilter;
};

#endif // DIGITALFILTERABSTRACT_H
