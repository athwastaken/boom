#pragma once

namespace bm {
	namespace draw {
		enum class shaderDataType {
			none = 0, float1, float2, float3, float4, mat3, mat4, int1, int2, int3, int4, boolean
		};

		static uint32_t shaderDataTypeSize(shaderDataType type) {
			switch (type)
			{
				case shaderDataType::float1:	return 4;
				case shaderDataType::float2:	return 8;
				case shaderDataType::float3:	return 12;
				case shaderDataType::float4:	return 16;
				case shaderDataType::mat3:		return 36;
				case shaderDataType::mat4:		return 64;
				case shaderDataType::int1:		return 4;
				case shaderDataType::int2:		return 8;
				case shaderDataType::int3:		return 12;
				case shaderDataType::int4:		return 16;
				case shaderDataType::boolean:	return 1;
			}

			BM_CORE_ASSERT(false, "Unknown shaderDataType.");
			return 0;
		}

		struct bufferElement {
			std::string name;
			shaderDataType type;
			uint32_t size;
			uint32_t offset;
			bool normalized;

			bufferElement() {};

			bufferElement(shaderDataType type, const std::string& name, bool normalized = false)
				: name(name), type(type), size(shaderDataTypeSize(type)), offset(0), normalized(normalized) {

			}

			uint32_t getComponentCount() const {
				switch (type) {
					case shaderDataType::float1:	return 1;
					case shaderDataType::float2:	return 2;
					case shaderDataType::float3:	return 3;
					case shaderDataType::float4:	return 4;
					case shaderDataType::mat3:		return 9;
					case shaderDataType::mat4:		return 16;
					case shaderDataType::int1:		return 1;
					case shaderDataType::int2:		return 2;
					case shaderDataType::int3:		return 3;
					case shaderDataType::int4:		return 4;
					case shaderDataType::boolean:	return 1;
				}

				BM_CORE_ASSERT(false, "Unknown shaderDataType.");
				return 0;
			}
		};

		class bufferLayout {
		public:
			bufferLayout() {};

			bufferLayout(const std::initializer_list<bufferElement>& element) : m_element(element) {
				calculateOffsetsAndStride();
			};

			inline uint32_t getStride() const { return m_stride; }
			inline const std::vector<bufferElement>& getElement() const { return m_element; }

			std::vector<bufferElement>::iterator begin() { return m_element.begin(); }
			std::vector<bufferElement>::iterator end() { return m_element.end(); }
			std::vector<bufferElement>::const_iterator begin() const { return m_element.begin(); }
			std::vector<bufferElement>::const_iterator end() const { return m_element.end(); }
		private:
			void calculateOffsetsAndStride() {
				uint32_t offset = 0;
				m_stride = 0;
				for (auto& element : m_element) {
					element.offset = offset;
					offset += element.size;
					m_stride += element.size;
				}
			};

			std::vector<bufferElement> m_element;
			uint32_t m_stride = 0;
		};

		class vertexBuffer {
		public:
			virtual ~vertexBuffer() {};

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual const bufferLayout& getLayout() const = 0;
			virtual void setLayout(const bufferLayout& layout) = 0;

			static vertexBuffer* create(float* vertices, uint32_t size);
		};

		class indexBuffer {
		public:
			virtual ~indexBuffer() {};

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual uint32_t getCount() const = 0;

			static indexBuffer* create(uint32_t* indices, uint32_t count);
		};
	}
}