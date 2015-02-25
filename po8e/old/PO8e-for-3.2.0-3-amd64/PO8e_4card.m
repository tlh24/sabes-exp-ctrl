classdef PO8e_4card
    properties
        CardPointer = cell(1,4);
        LibName = '';
        StoppedPointer = cell(1,4);
        BufferPointer = cell(1,4);
        Data = cell(1,4);
        Offsets = cell(1,4);
        Status = zeros(1,4);
        NChannels = zeros(1,4);
        NBlocks = zeros(1,4);
        SampleSize = zeros(1,4);
    end
    
    methods
        function obj = PO8e_4card()
            lib = 'PO8eStreaming';
            if strfind(computer, 'WIN')
                ext = '.dll';
            else
                ext = '.so';
            end
            if libisloaded(lib)
                unloadlibrary(lib)
            end
            [~,warnings] = loadlibrary([lib ext], 'PO8e_Matlab.h');
            if ~isempty(warnings)
                warnings
            end
            
            if libisloaded(lib)
                disp(['Library ' lib ' loaded successfully']);
            else
                error(['Unable to load library ' [lib ext]])
            end
            
            %display all available functions and their signatures
            M = libfunctions(lib, '-full');
            obj.LibName = lib;
            for i = 1:4
                obj.StoppedPointer{i} = libpointer('bool', false);
            end
        end
            
        function b = isNull(obj, index)
            b = obj.CardPointer{index} == 0;
        end
        
        function b = isStopped(obj, index)
            b = obj.StoppedPointer{index} == 1;
        end
        
        function total = cardCount(obj)
            total = calllib(obj.LibName, 'cardCount');
        end
        
        function obj = connectToCard(obj, index)
            obj.CardPointer{index} = calllib(obj.LibName, 'connectToCard', index-1);
        end
        
        function obj = releaseCard(obj, index)
            calllib(obj.LibName, 'releaseCard', obj.CardPointer{index});
        end
        
        function x = startCollecting(obj, index, detectStops)
           x = calllib(obj.LibName, 'startCollecting', obj.CardPointer{index}, detectStops);
        end
        
        function x = getLastError(obj, index)
            x = calllib(obj.LibName, 'getLastError', obj.CardPointer{index});
        end
        
        function obj = getStreamInfo(obj, index)
            obj.NChannels(index) = calllib(obj.LibName, 'numChannels', obj.CardPointer{index});
            obj.NBlocks(index) = calllib(obj.LibName, 'numBlocks', obj.CardPointer{index});
            obj.SampleSize(index) = calllib(obj.LibName, 'dataSampleSize', obj.CardPointer{index});
        end
            
        function waitForDataReady(obj, index, timeout)
            calllib(obj.LibName, 'waitForDataReady', obj.CardPointer{index}, timeout);
        end
        
        function [numSamples, obj] = samplesReady(obj, index)
            [numSamples, p, obj.StoppedPointer{index}] = calllib(obj.LibName, 'samplesReady', obj.CardPointer{index}, obj.StoppedPointer{index});
        end
        
        function obj = readBlock(obj, index, nSamples)
            obj = obj.getStreamInfo(index);
            buffer = zeros(1, nSamples*obj.NChannels(index));
            switch obj.SampleSize(index)
                case 4
                    %pBuffer = libpointer('voidPtr', int32(buffer));
                    pBuffer = libpointer('voidPtr', single(buffer));
                case 2
                    pBuffer = libpointer('voidPtr', int16(buffer));
                case 1
                    pBuffer = libpointer('voidPtr', int8(buffer));                
                otherwise
                    error('sampleSize %d unrecognized', obj.SampleSize(index))
            end
            iBuffer = libpointer('int64Ptr', int64(zeros(1,nSamples)));
            obj.Status(index) = calllib(obj.LibName, 'readBlock', obj.CardPointer{index}, pBuffer, nSamples, iBuffer);
            %obj.Data{index} = pBuffer.Value;
            obj.Data{index} = reshape(pBuffer.Value, nSamples, numel(pBuffer.Value)/nSamples)';
            obj.Offsets{index} = iBuffer.Value;
            clear pBuffer;
        end
        
        function flushBufferedData(obj, index, nSamples, release)
            calllib(obj.LibName, 'flushBufferedData', obj.CardPointer{index}, nSamples, release);
        end
    end
end
