/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#pragma once

#include <AzToolsFramework/ToolsComponents/EditorComponentBase.h>
#include <Maestro/Bus/EditorSequenceAgentComponentBus.h>
#include "SequenceAgent.h"

namespace AzToolsFramework
{
    namespace Components
    {
        class TransformComponent;
    }
}
namespace Maestro
{
    class EditorSequenceAgentComponent
        : public AzToolsFramework::Components::EditorComponentBase
        , public EditorSequenceAgentComponentRequestBus::MultiHandler
        , public SequenceAgentComponentRequestBus::MultiHandler
        , public SequenceAgent
    {
    public:
        AZ_EDITOR_COMPONENT(EditorSequenceAgentComponent, "{D90A3A45-CA0C-4ED7-920A-41D50557D67B}");

        //////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;
        //////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////
        // EditorSequenceAgentComponentRequestBus::Handler Interface
        void GetAllAnimatableProperties(IAnimNode::AnimParamInfos& properties, AZ::ComponentId componentId) override;
        void GetAnimatableComponents(AZStd::vector<AZ::ComponentId>& animatableComponentIds) override;
        //~EditorSequenceAgentComponentRequestBus::Handler Interface //////////////////

        //////////////////////////////////////////////////////////////////////////
        // SequenceAgentComponentRequestBus::Handler Interface
        void ConnectSequence(const AZ::EntityId& sequenceEntityId) override;
        void DisconnectSequence() override;

        AZ::Uuid GetAnimatedAddressTypeId(const AnimatablePropertyAddress& animatableAddress) override;

        void GetAnimatedPropertyValue(AnimatedValue& returnValue, const AnimatablePropertyAddress& animatableAddress) override;
        bool SetAnimatedPropertyValue(const AnimatablePropertyAddress& animatableAddress, const AnimatedValue& value) override;

        void GetAssetDuration(AnimatedValue& returnValue, AZ::ComponentId componentId, const AZ::Data::AssetId& assetId) override;

        //~SequenceAgentComponentRequestBus::Handler Interface //////////////////

    protected:
        // Required Reflect function.
        static void Reflect(AZ::ReflectContext* context);

        // Optional functions for defining provided and dependent services.
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
        {
            dependent.push_back(AZ_CRC("TransformService", 0x8ee22c50));
        }
       
        // Override from SequenceAgent
        const AZ::Uuid& GetComponentTypeUuid(const AZ::Component& component) const override;

        ////////////////////////////////////////////////////////////////////////
        void BuildGameEntity(AZ::Entity* gameEntity) override;
        ////////////////////////////////////////////////////////////////////////

    private:
        // connect and disconnect to all SequenceComponents registered with us
        void ConnectAllSequences();
        void DisconnectAllSequences();

        // set of ids of all unique Entities with SequenceComponent instances connected to this Agent
        AZStd::unordered_set<AZ::EntityId>             m_sequenceEntityIds;
    };
} // namespace Maestro