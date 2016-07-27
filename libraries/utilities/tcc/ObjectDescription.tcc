////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     ObjectDescription.tcc (utilities)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace utilities
{
    template <typename ValueType>
    ObjectDescription ObjectDescription::FromType() 
    {
        auto result = ObjectDescription(std::is_fundamental<typename std::decay<ValueType>::type>::value);
        result._typeName = TypeName<typename std::decay<ValueType>::type>::GetName();
        return result;
    }

    template <typename ValueType>
    ObjectDescription ObjectDescription::FromType(ValueType&& obj)
    {
        return FromType<ValueType>();
    }

    template <typename ValueType>
    void ObjectDescription::AddField(std::string name, ValueType&& value)
    {
        _description.insert(std::make_pair(name, MakeVariant<typename std::decay<ValueType>::type>(value)));
    }
}
